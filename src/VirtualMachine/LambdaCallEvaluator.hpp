//
// Created by caedus on 30.01.2021.
//

#pragma once

#include "TypeSystem/Types/LambdaObject.hpp"
#include "Runtime/GenericEvaluator.hpp"
#include "Utilities/LispCast.hpp"

namespace nastya::vm {

class LambdaCallEvaluator : public runtime::GenericEvaluator {
public:
    LambdaCallEvaluator(const typesystem::ObjectStorage& callee, const std::vector<typesystem::ObjectStorage>& call,
                        runtime::IMachine& machine);
    typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                           runtime::IMachine& vm) const override;
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;
    void postExecute(runtime::IMachine& vm) const override;
private:
    runtime::IMachine& m_machine;
    const std::vector<typesystem::ObjectStorage>& m_call;
    const typesystem::LambdaObject& m_callee;
};

}
