//
// Created by caedus on 12.12.2020.
//

#pragma once

#include <string>

#include "LispExpression/TypeSystem/GenericObject.hpp"
#include "LispExpression/TypeSystem/ComparableTrait.hpp"

namespace nastya::lisp::typesystem {
class LabelObject : public GenericObject, public NonComparableObject
{
public:
    LabelObject(std::string value);
    std::string getValue() const;
    IObject* clone() const override;
    std::string toString() const override;
    std::string info() const override;

private:
    std::string m_value;
};
}  // namespace nastya::lisp::typesystem
