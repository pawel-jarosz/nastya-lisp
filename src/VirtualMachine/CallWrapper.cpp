//
// Created by caedus on 30.01.2021.
//

#include "VirtualMachine/CallWrapper.hpp"

namespace nastya::vm {
CallWrapper::CallWrapper(const runtime::IEvaluator& evaluator)
: runtime::GenericEvaluator("CallWrapper"), m_evaluator{&evaluator}, m_state{CallWrapperState::Reference}
{
}

CallWrapper::CallWrapper(const runtime::IEvaluator* evaluator)
: runtime::GenericEvaluator("CallWrapper"), m_evaluator{evaluator}, m_state{CallWrapperState::Pointer}
{
}

CallWrapper::~CallWrapper()
{
    if (m_state == CallWrapperState::Pointer)
    {
        delete m_evaluator;
    }
}
typesystem::ObjectStorage CallWrapper::preExecute(const typesystem::ListObject& object, runtime::IMachine& vm) const
{
    return m_evaluator->preExecute(object, vm);
}

typesystem::ObjectStorage CallWrapper::evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const
{
    return m_evaluator->evaluate(memory, object);
}

void CallWrapper::postExecute(runtime::IMachine& vm) const
{
    m_evaluator->postExecute(vm);
}

}  // namespace nastya::vm
