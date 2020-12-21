//
// Created by caedus on 16.12.2020.
//

#pragma once

#include "Runtime/Interface/IMemory.hpp"
#include "LispExpression/ObjectStorage.hpp"

namespace nastya::runtime {

class IEvaluator {
public:
    virtual std::string getName() const = 0;
    virtual lisp::ObjectStorage evaluate(IMemory& memory, const lisp::ObjectStorage& object) const = 0;
};

}
