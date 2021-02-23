//
// Created by caedus on 12.12.2020.
//

#pragma once

#include "ComparableTrait.hpp"
#include "GenericObject.hpp"

namespace nastya::typesystem {

class NumberObject : public GenericObject, public ComparableObject
{
public:
    NumberObject();
    explicit NumberObject(int value);
    explicit NumberObject(float value);
    NumberObject(const NumberObject& rhs);
    NumberObject(NumberObject&& rhs);

    NumberObject& operator=(const NumberObject& rhs);
    NumberObject& operator=(NumberObject&& rhs);

    NumberType getNumberType() const;
    int getInteger() const;
    float getFloating() const;
    IObject* clone() const override;
    std::string toString() const override;
    std::string info() const override;
    int compare(const IObject& rhs) const override;
private:
    union
    {
        float m_float_value;
        int m_int_value;
    };
    NumberType m_type;
};
}  // namespace nastya::typesystem
