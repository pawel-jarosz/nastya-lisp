//
// Created by caedus on 13.12.2020.
//

#pragma once

#include "LispExpression/Interface/IObject.hpp"

namespace nastya::lisp {

class IObjectStorage
{
public:
    virtual ~IObjectStorage() = default;
    virtual IObject& getRawObject() const = 0;
    virtual ObjectType getType() const = 0;
};
}  // namespace nastya::lisp
