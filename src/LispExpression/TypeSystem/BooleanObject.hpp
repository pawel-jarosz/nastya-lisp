//
// Created by caedus on 12.12.2020.
//

#pragma once

#include "LispExpression/TypeSystem/GenericObject.hpp"
#include "LispExpression/TypeSystem/ComparableTrait.hpp"

namespace nastya::lisp::typesystem {
class BooleanObject : public GenericObject, public NonComparableObject
{
public:
    BooleanObject(bool value);
    bool getValue() const;
    IObject* clone() const override;
    std::string toString() const override;
    std::string info() const override;
private:
    bool m_value;
};
}  // namespace nastya::lisp::typesystem
