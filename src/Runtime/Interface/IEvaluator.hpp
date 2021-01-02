//
// Created by caedus on 16.12.2020.
//

#pragma once

#include "LispExpression/ObjectStorage.hpp"
#include "Runtime/Interface/IMemory.hpp"

namespace nastya::runtime {

class IEvaluator
{
public:
    virtual std::string getName() const = 0;
    virtual lisp::ObjectStorage evaluate(IMemory& memory, const lisp::ObjectStorage& object) const = 0;
};

}  // namespace nastya::runtime
