//
// Created by caedus on 12.12.2020.
//

#pragma once

#include "ComparableTrait.hpp"
#include "GenericObject.hpp"

namespace nastya::typesystem {
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
}  // namespace nastya::typesystem
