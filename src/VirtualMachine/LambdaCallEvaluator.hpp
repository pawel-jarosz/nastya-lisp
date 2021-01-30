//
// Created by caedus on 30.01.2021.
//

#pragma once

#include "LispExpression/TypeSystem/LambdaObject.hpp"
#include "Runtime/GenericEvaluator.hpp"
#include "Utilities/LispCast.hpp"

namespace nastya::vm {

class LambdaCallEvaluator : public runtime::GenericEvaluator {
public:
    LambdaCallEvaluator(const lisp::ObjectStorage& callee, const std::vector<lisp::ObjectStorage>& call,
                        runtime::IMachine& machine);
    lisp::ObjectStorage preExecute(const lisp::typesystem::ListObject& object,
                                           runtime::IMachine& vm) const override;
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
    void postExecute(runtime::IMachine& vm) const override;
private:
    runtime::IMachine& m_machine;
    const std::vector<lisp::ObjectStorage>& m_call;
    const lisp::typesystem::LambdaObject& m_callee;
};

}
