//
// Created by caedus on 30.01.2021.
//

#pragma once

#include <Runtime/GenericEvaluator.hpp>
#include <variant>

namespace nastya::vm {

class CallWrapper : public runtime::GenericEvaluator {
public:
    explicit CallWrapper(const runtime::IEvaluator& evaluator);
    explicit CallWrapper(const runtime::IEvaluator* evaluator);
    ~CallWrapper();
    lisp::ObjectStorage preExecute(const lisp::typesystem::ListObject& object,
                                           runtime::IMachine& vm) const override;
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
    void postExecute(runtime::IMachine& vm) const override;
private:
    enum class CallWrapperState {
        Pointer,
        Reference
    };
    const IEvaluator* m_evaluator;
    CallWrapperState m_state;
};

}