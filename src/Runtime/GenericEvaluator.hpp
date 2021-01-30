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
    virtual std::string getName() const override;
    virtual lisp::ObjectStorage preExecute(const lisp::typesystem::ListObject& object,
                                           IMachine& vm) const override;
private:
    std::string m_name;
};

}  // namespace nastya::runtime
