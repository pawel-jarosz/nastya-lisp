//
// Created by caedus on 30.01.2021.
//

#include "VirtualMachine/CallWrapper.hpp"

namespace nastya::vm {
CallWrapper::CallWrapper(const runtime::IEvaluator& evaluator)
: runtime::GenericEvaluator("CallWrapoer")
, m_evaluator{&evaluator}
, m_state{CallWrapperState::Reference}
{
}

CallWrapper::CallWrapper(const runtime::IEvaluator* evaluator)
    : runtime::GenericEvaluator("CallWrapoer")
    , m_evaluator{evaluator}
    , m_state{CallWrapperState::Pointer}
{
}

CallWrapper::~CallWrapper()
{
    if (m_state == CallWrapperState::Pointer) {
        delete m_evaluator;
    }
}
lisp::ObjectStorage CallWrapper::preExecute(const lisp::typesystem::ListObject& object, runtime::IMachine& vm) const
{
    return m_evaluator->preExecute(object, vm);
}

lisp::ObjectStorage CallWrapper::evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const
{
    return m_evaluator->evaluate(memory, object);
}

void CallWrapper::postExecute(runtime::IMachine& vm) const
{
    m_evaluator->postExecute(vm);
}

}
