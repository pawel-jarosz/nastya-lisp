//
// Created by caedus on 15.12.2020.
//

#pragma once

#include <memory>

#include "LispExpression/Interface/IObject.hpp"
#include "LispExpression/ObjectStorage.hpp"

namespace nastya::lisp {

class IExpressionBuilder
{
public:
    virtual ~IExpressionBuilder() = default;
    virtual ObjectStorage build() = 0;
    virtual void reset() = 0;
};
}  // namespace nastya::lisp
