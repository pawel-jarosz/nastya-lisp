//
// Created by caedus on 09.01.2021.
//

#pragma once

#include "LispExpression/Interface/IObject.hpp"

namespace nastya::lisp::typesystem {

struct HasComparableTrait {
    virtual bool isComparable() const = 0;
};

class NonComparableObject : public HasComparableTrait {
public:
    bool isComparable() const final { return false; }
};

class ComparableObject : public HasComparableTrait {
public:
    bool isComparable() const final { return true; }
    virtual int compare(const IObject& rhs) const = 0;
};

}
