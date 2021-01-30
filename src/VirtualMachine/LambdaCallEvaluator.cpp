//
// Created by caedus on 30.01.2021.
//

#include "VirtualMachine/LambdaCallEvaluator.hpp"

namespace nastya::vm {
LambdaCallEvaluator::LambdaCallEvaluator(const lisp::ObjectStorage& callee,  const std::vector<lisp::ObjectStorage>& call,
                                        runtime::IMachine& machine)
: runtime::GenericEvaluator{"LambdaCall"}
, m_callee{utils::Cast::as_lambda(callee, "Label should be computed to be lambda...")}
, m_call{call}
, m_machine{machine}
{
}

lisp::ObjectStorage LambdaCallEvaluator::preExecute(const lisp::typesystem::ListObject& object, runtime::IMachine& vm) const
{
    m_machine.pushStackFrame();
    const auto& arguments = m_callee.getArgumentsList();
    for (int i = 1; i < m_call.size(); i++) {
        const auto computed_value = m_machine.run(m_call[i]);
        const auto argument_name = utils::Cast::as_label(arguments.getContent()[i - 1],
                                                         "Name of variable should be label");
        m_machine.registerVariableOnStack(argument_name, computed_value);
    }
    return lisp::ObjectStorage();
}

lisp::ObjectStorage LambdaCallEvaluator::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const
{
    lisp::ObjectStorage command{std::unique_ptr<lisp::IObject>(m_callee.getCommand().clone())};
    const auto result = m_machine.run(command);
    return result;
}

void LambdaCallEvaluator::postExecute(runtime::IMachine&) const
{
    m_machine.popStackFrame();
}

}