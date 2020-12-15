//
// Created by caedus on 15.12.2020.
//

#pragma once

#include "LispExpression/Interface/IObject.hpp"
#include "LispExpression/ObjectStorage.hpp"

#include <memory>

namespace nastya::lisp {

class IExpressionBuilder {
public:
    virtual ~IExpressionBuilder() = default;
    virtual ObjectStorage build() = 0;
};
}
