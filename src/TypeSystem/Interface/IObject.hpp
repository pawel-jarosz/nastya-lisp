//
// Created by caedus on 12.12.2020.
//

#pragma once

#include <string>

#include "TypeSystem/Types/ObjectType.hpp"

namespace nastya::typesystem {
class IObject
{
public:
    virtual ~IObject() = default;
    virtual ObjectType getType() const = 0;
    virtual IObject* clone() const = 0;
    virtual std::string toString() const = 0;
    virtual std::string info() const = 0;
};
}  // namespace nastya::parser
