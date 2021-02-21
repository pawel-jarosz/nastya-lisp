//
// Created by caedus on 13.12.2020.
//

#pragma once

#include "IObject.hpp"

namespace nastya::typesystem {

class IObjectStorage
{
public:
    virtual ~IObjectStorage() = default;
    virtual IObject& getRawObject() const = 0;
    virtual ObjectType getType() const = 0;
};
}  // namespace nastya::parser
