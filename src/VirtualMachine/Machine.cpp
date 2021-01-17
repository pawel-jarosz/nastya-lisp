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
    if (list.getType() == lisp::ObjectType::Label and isSymbolAvailable(list)) {
        return getFromHeap(Cast::as_label(list));
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
    const auto reversed_stack = m_stack | ranges::views::reverse;
    for (const auto frame: reversed_stack) {
        try {
            return frame.at(variableName.getValue());
        }
        catch(std::exception& e) {
            continue;
        }
    }
    BUT_THROW(MachineRuntimeException, "Variable is not available");
}

}  // namespace nastya::vm
