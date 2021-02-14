//
// Created by caedus on 13.02.2021.
//

#include "TypeSystem/Types/BooleanObject.hpp"
#include <sstream>

namespace nastya::typesystem {
BooleanObject::BooleanObject(bool value) : GenericObject(ObjectType::Boolean), m_value{value}
{
}

bool BooleanObject::getValue() const
{
    return m_value;
}

IObject* BooleanObject::clone() const
{
    return new BooleanObject(*this);
}

std::string BooleanObject::toString() const
{
    if (m_value)
    {
        return "#true";
    }
    return "#false";
}

std::string BooleanObject::info() const
{
    std::stringstream ss;
    ss << "Boolean => " << toString();
    return ss.str();
}

}
