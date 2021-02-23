//
// Created by caedus on 13.02.2021.
//

#include <sstream>

#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/TypeSystemError.hpp"

namespace nastya::typesystem {
NumberObject::NumberObject() : NumberObject(0)
{
}

NumberObject::NumberObject(int value)
: GenericObject(ObjectType::Number), m_int_value(value), m_type{NumberType::Integer}
{
}

NumberObject::NumberObject(float value)
: GenericObject(ObjectType::Number), m_float_value(value), m_type{NumberType::Floating}
{
}

NumberObject::NumberObject(const NumberObject& rhs) : GenericObject(ObjectType::Number), m_type{NumberType::Integer}
{
    m_type = rhs.m_type;
    if (m_type == NumberType::Integer)
    {
        m_int_value = rhs.m_int_value;
    }
    else
    {
        m_float_value = rhs.m_float_value;
    }
}

NumberObject::NumberObject(NumberObject&& rhs) : GenericObject(ObjectType::Number), m_type{NumberType::Integer}
{
    m_type = rhs.m_type;
    if (m_type == NumberType::Integer)
    {
        m_int_value = rhs.m_int_value;
    }
    else
    {
        m_float_value = rhs.m_float_value;
    }
}

NumberObject& NumberObject::operator=(const NumberObject& rhs)
{
    m_type = rhs.m_type;
    if (m_type == NumberType::Integer)
    {
        m_int_value = rhs.m_int_value;
    }
    else
    {
        m_float_value = rhs.m_float_value;
    }
    return *this;
}

NumberObject& NumberObject::operator=(NumberObject&& rhs)
{
    m_type = rhs.m_type;
    if (m_type == NumberType::Integer)
    {
        m_int_value = rhs.m_int_value;
    }
    else
    {
        m_float_value = rhs.m_float_value;
    }
    return *this;
}

float NumberObject::getFloating() const
{
    if (m_type == NumberType::Integer)
    {
        BUT_THROW(TypeSystemError, "Number is floating");
    }
    return m_float_value;
}

int NumberObject::getInteger() const
{
    if (m_type == NumberType::Floating)
    {
        BUT_THROW(TypeSystemError, "Number is integer");
    }
    return m_int_value;
}

NumberType NumberObject::getNumberType() const
{
    return m_type;
}

IObject* NumberObject::clone() const
{
    return new NumberObject(*this);
}

std::string NumberObject::toString() const
{
    std::stringstream ss;
    if (m_type == NumberType::Integer)
    {
        ss << m_int_value;
        return ss.str();
    }
    ss << m_float_value;
    return ss.str();
}

std::string NumberObject::info() const
{
    std::stringstream ss;
    if (getNumberType() == NumberType::Floating)
    {
        ss << "Floating => ";
    }
    else
    {
        ss << "Integer => ";
    }
    ss << toString();
    return ss.str();
}

int compare_int(const int lhs, const int rhs)
{
    if (lhs < rhs)
    {
        return -1;
    }
    else if (lhs == rhs)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int compare_float(const float lhs, const float rhs)
{
    if (lhs < rhs)
    {
        return -1;
    }
    else if (lhs == rhs)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int compare_number(const int value, const NumberObject& rhs)
{
    if (rhs.getNumberType() == NumberType::Integer)
    {
        return compare_int(value, rhs.getInteger());
    }
    return compare_float(value, rhs.getFloating());
}

int compare_number(const float value, const NumberObject& rhs)
{
    if (rhs.getNumberType() == NumberType::Floating)
    {
        return compare_int(value, rhs.getFloating());
    }
    return compare_float(value, rhs.getInteger());
}

int NumberObject::compare(const IObject& rhs) const
{
    if (rhs.getType() != ObjectType::Number)
    {
        BUT_THROW(TypeSystemError, "Given arguments are not comparable");
    }
    auto casted_rhs = dynamic_cast<const NumberObject&>(rhs);
    if (m_type == NumberType::Integer)
    {
        return compare_number(m_int_value, casted_rhs);
    }
    return compare_number(m_float_value, casted_rhs);
}

}  // namespace nastya::typesystem
