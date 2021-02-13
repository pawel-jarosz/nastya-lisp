//
// Created by caedus on 09.01.2021.
//

#pragma once

#include "TypeSystem/Interface/IObject.hpp"

namespace nastya::lisp::typesystem {

struct HasEqualTrait {
    virtual bool equal(const IObject& object) const = 0;
};

}
