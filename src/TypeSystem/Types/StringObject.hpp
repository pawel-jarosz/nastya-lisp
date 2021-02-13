//
// Created by caedus on 12.12.2020.
//

#pragma once

#include <string>

#include "ComparableTrait.hpp"
#include "GenericObject.hpp"

namespace nastya::lisp::typesystem {
class StringObject : public GenericObject, public ComparableObject
{
public:
    StringObject(std::string value);
    std::string getValue() const;
    IObject* clone() const override;
    std::string toString() const override;
    std::string info() const override;
    int compare(const IObject& rhs) const override;
private:
    std::string m_value;
};
}  // namespace nastya::lisp::typesystem
