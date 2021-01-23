//
// Created by caedus on 22.12.2020.
//

#include <algorithm>

#include <Utilities/LispCast.hpp>

#include "Builtins/BuiltinsException.hpp"
#include "LispExpression/TypeSystem/LabelObject.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "Modules/ModuleException.hpp"
#include "VirtualMachine/Machine.hpp"
#include "VirtualMachine/MachineRuntimeException.hpp"
#include <iostream>
#include <range/v3/view.hpp>

namespace nastya::vm {
using namespace utils;

Machine::Machine(const modules::IModuleRegistry& registry, const IArgumentPreparationManager& preparation_manager)
: m_modules{registry}
, m_preparation_manager{preparation_manager}
{
}

lisp::ObjectStorage Machine::run(const lisp::ObjectStorage& list)
{
    const auto label_computation_result = computeLabel(list);
    if (label_computation_result) {
        return *label_computation_result;
    }
    if (list.getType() != lisp::ObjectType::List)
    {
        return list;
    }
    // GCOVR_EXCL_START
    //
    // Casts does not required to be check for bad_cast error because type are checked with enum.
    // Index is correct because earlier we checked if it is not empty list.
    const auto& raw_object = Cast::as_list(list);
    if (raw_object.isEmpty()) {
        return lisp::ObjectStorage(list);
    }
    auto content = raw_object.getContent();
    if (content[0].getType() != lisp::ObjectType::Label) {
        BUT_THROW(MachineRuntimeException, "Invalid command format");
    }
    auto label = dynamic_cast<lisp::typesystem::LabelObject&>(content[0].getRawObject());
    // GCOVR_EXCL_STOP
    auto lambda = computeLabel(content[0]);
    if (lambda and lambda.value().getType() == lisp::ObjectType::Lambda) {
        return computeLambda(lambda.value(), content);
    }
    const auto& strategy = m_preparation_manager.getStrategy(label.getValue());
    const auto arguments = strategy.extract_arguments(raw_object, *this);
    return m_modules.getFunction(label.getValue()).evaluate(*this, arguments);
}

bool Machine::registerVariableOnHeap(const lisp::typesystem::LabelObject& variableName,
                                     const lisp::ObjectStorage& objectStorage)
{
    auto [it, state] = m_heap.try_emplace(variableName.getValue(), objectStorage);
    return state;
}

const lisp::ObjectStorage& Machine::getFromHeap(const lisp::typesystem::LabelObject& variableName) const
{
    try {
        return m_heap.at(variableName.getValue());
    }
    catch(std::exception& e) {
        BUT_THROW(MachineRuntimeException, "Variable is not available");
    }
}

bool Machine::isSymbolAvailable(const lisp::ObjectStorage& object) const
{
    const auto& label = utils::Cast::as_label(object);
    const auto reversed_stack = m_stack | ranges::views::reverse;
    for (const auto frame: reversed_stack) {
        if (frame.find(label.getValue()) != frame.end()) {
            return true;
        }
    }
    return (m_heap.find(label.getValue()) != m_heap.end());
}

void Machine::pushStackFrame()
{
    m_stack.emplace_back(std::map<std::string, lisp::ObjectStorage>());
}

bool Machine::popStackFrame()
{
    if (not m_stack.empty()) {
        m_stack.pop_back();
        return true;
    }
    return false;
}

bool Machine::registerVariableOnStack(const lisp::typesystem::LabelObject& variableName,
                                      const lisp::ObjectStorage& objectStorage)
{
    if (m_stack.empty()) {
        pushStackFrame();
    }
    const auto top = m_stack.size() - 1;
    auto [it, state] =  m_stack[top].try_emplace(variableName.toString(), objectStorage);
    return false;
}

const lisp::ObjectStorage& Machine::getFromStack(const lisp::typesystem::LabelObject& variableName) const
{
    auto it = m_stack.rbegin();
    while (it != m_stack.rend()) {
        const auto result = it->find(variableName.getValue());
        if (result != it->end()) {
            return result->second;
        }
    }
    BUT_THROW(MachineRuntimeException, "Variable is not available");
}

std::optional<lisp::ObjectStorage> Machine::computeLabel(const lisp::ObjectStorage& label) const
{
    if (label.getType() != lisp::ObjectType::Label) {
        return {};
    }

    if (not isSymbolAvailable(label)) {
        return label;
    }
    try {
        std::unique_ptr<lisp::IObject> copied(getFromStack(Cast::as_label(label)).getRawObject().clone());
        lisp::ObjectStorage result(std::move(copied));
        return { result };
    }
    catch(MachineRuntimeException& e) {
        const auto result = getFromHeap(Cast::as_label(label));
        return { result };
    }
}

lisp::ObjectStorage
Machine::computeLambda(const lisp::ObjectStorage& lambda_storage, const std::vector<lisp::ObjectStorage>& call)
{
    const auto& lambda = utils::Cast::as_lambda(lambda_storage, "Label should be computed to be lambda...");
    pushStackFrame();
    const auto& arguments = lambda.getArgumentsList();
    for (int i = 1; i < call.size(); i++) {
        const auto computed_value = run(call[i]);
        const auto argument_name = utils::Cast::as_label(arguments.getContent()[i - 1],
                                                         "Name of variable should be label");
        registerVariableOnStack(argument_name, computed_value);
    }
    lisp::ObjectStorage command{std::unique_ptr<lisp::IObject>(lambda.getCommand().clone())};
    const auto result = run(command);
    popStackFrame();
    return result;
}

}  // namespace nastya::vm
