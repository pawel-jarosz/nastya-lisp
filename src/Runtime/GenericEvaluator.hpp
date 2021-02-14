//
// Created by caedus on 30.01.2021.
//

#pragma once

#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::runtime {

class GenericEvaluator : public IEvaluator
{
public:
    explicit GenericEvaluator(std::string name);
    std::string getName() const override;
    typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                           IMachine& vm) const override;
    void postExecute(IMachine& vm) const override;
private:
    std::string m_name;
};

}  // namespace nastya::runtime
