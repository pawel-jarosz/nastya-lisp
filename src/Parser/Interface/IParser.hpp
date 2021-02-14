//
// Created by caedus on 15.12.2020.
//

#pragma once

#include <memory>

#include "TypeSystem/Interface/IObject.hpp"
#include "TypeSystem/ObjectStorage.hpp"

namespace nastya::lisp {

class IParser
{
public:
    virtual ~IParser() = default;
    virtual typesystem::ObjectStorage build() = 0;
    virtual void reset() = 0;
};
}  // namespace nastya::lisp
