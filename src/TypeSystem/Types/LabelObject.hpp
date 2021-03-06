//
// Created by caedus on 12.12.2020.
//

#pragma once

#include <string>

#include "ComparableTrait.hpp"
#include "GenericObject.hpp"

namespace nastya::typesystem {
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
}  // namespace nastya::typesystem
