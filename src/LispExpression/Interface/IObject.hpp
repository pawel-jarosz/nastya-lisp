//
// Created by caedus on 12.12.2020.
//

#pragma once

#include <string>

#include "LispExpression/TypeSystem/ObjectType.hpp"

namespace nastya::lisp {
class IObject
{
public:
    virtual ~IObject() = default;
    virtual ObjectType getType() const = 0;
    virtual IObject* clone() const = 0;
    virtual std::string toString() const = 0;
};
}  // namespace nastya::lisp
