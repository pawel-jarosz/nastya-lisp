//
// Created by caedus on 22.12.2020.
//

#include <algorithm>

#include <Utilities/LispCast.hpp>
#include <range/v3/view.hpp>

#include "Builtins/BuiltinsException.hpp"
#include "Modules/ModuleException.hpp"
#include "TypeSystem/Types/LabelObject.hpp"
#include "TypeSystem/Types/ListObject.hpp"
#include "VirtualMachine/CallWrapper.hpp"
#include "VirtualMachine/LambdaCallEvaluator.hpp"
#include "VirtualMachine/Machine.hpp"
#include "VirtualMachine/MachineRuntimeException.hpp"

namespace nastya::vm {
using namespace utils;

Machine::Machine(const modules::IModuleRegistry& registry) : m_modules{registry}
{
}

typesystem::ObjectStorage Machine::run(const typesystem::ObjectStorage& list)
{
    const auto label_computation_result = computeLabel(list);
    if (label_computation_result)
    {
        return *label_computation_result;
    }
    if (list.getType() != typesystem::ObjectType::List)
    {
        return list;
    }
    // GCOVR_EXCL_START
    //
    // Casts does not required to be check for bad_cast error because type are checked with enum.
    // Index is correct because earlier we checked if it is not empty list.
    const auto& raw_object = Cast::as_list(list);
    if (raw_object.isEmpty())
    {
        return typesystem::ObjectStorage(list);
    }
    auto content = raw_object.getContent();
    if (content[0].getType() != typesystem::ObjectType::Label)
    {
        BUT_THROW(MachineRuntimeException, "Invalid command format");
    }
    auto label = dynamic_cast<typesystem::LabelObject&>(content[0].getRawObject());
    // GCOVR_EXCL_STOP
    auto lambda = computeLabel(content[0]);
    const auto isLambda = (lambda and lambda.value().getType() == typesystem::ObjectType::Lambda);
    std::unique_ptr<CallWrapper> call;
    if (isLambda)
    {
        call = std::make_unique<CallWrapper>(new LambdaCallEvaluator(lambda.value(), content, *this));
    }
    else
    {
        call = std::make_unique<CallWrapper>(m_modules.getFunction(label.getValue()));
    }

    const auto arguments = call->preExecute(raw_object, *this);
    const auto result = call->evaluate(*this, arguments);
    call->postExecute(*this);
    return result;
}

bool Machine::registerVariableOnHeap(const typesystem::LabelObject& variableName,
                                     const typesystem::ObjectStorage& objectStorage)
{
    auto [it, state] = m_heap.try_emplace(variableName.getValue(), objectStorage);
    return state;
}

const typesystem::ObjectStorage& Machine::getFromHeap(const typesystem::LabelObject& variableName) const
{
    return m_heap.at(variableName.getValue());
}

bool Machine::isSymbolAvailable(const typesystem::ObjectStorage& object) const
{
    const auto& label = utils::Cast::as_label(object);
    const auto reversed_stack = m_stack | ranges::views::reverse;
    for (const auto frame : reversed_stack)
    {
        if (frame.find(label.getValue()) != frame.end())
        {
            return true;
        }
    }
    return (m_heap.find(label.getValue()) != m_heap.end());
}

void Machine::pushStackFrame()
{
    m_stack.emplace_back(std::map<std::string, typesystem::ObjectStorage>());
}

bool Machine::popStackFrame()
{
    if (not m_stack.empty())
    {
        m_stack.pop_back();
        return true;
    }
    return false;
}

bool Machine::registerVariableOnStack(const typesystem::LabelObject& variableName,
                                      const typesystem::ObjectStorage& objectStorage)
{
    if (m_stack.empty())
    {
        pushStackFrame();
    }
    const auto top = m_stack.size() - 1;
    auto [it, state] = m_stack[top].try_emplace(variableName.toString(), objectStorage);
    return false;
}

const typesystem::ObjectStorage& Machine::getFromStack(const typesystem::LabelObject& variableName) const
{
    auto it = m_stack.rbegin();
    while (it != m_stack.rend())
    {
        const auto result = it->find(variableName.getValue());
        if (result != it->end())
        {
            return result->second;
        }
        it += 1;
    }
    BUT_THROW(MachineRuntimeException, "Variable is not available");
}

std::optional<typesystem::ObjectStorage> Machine::computeLabel(const typesystem::ObjectStorage& label) const
{
    if (label.getType() != typesystem::ObjectType::Label)
    {
        return {};
    }
    if (not isSymbolAvailable(label))
    {
        return label;
    }
    try
    {
        std::unique_ptr<typesystem::IObject> copied(getFromStack(Cast::as_label(label)).getRawObject().clone());
        typesystem::ObjectStorage result(std::move(copied));
        return {result};
    }
    catch (MachineRuntimeException& e)
    {
        const auto result = getFromHeap(Cast::as_label(label));
        return {result};
    }
}

}  // namespace nastya::vm
