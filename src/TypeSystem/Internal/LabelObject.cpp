//
// Created by caedus on 13.02.2021.
//

#include <sstream>

#include "TypeSystem/Types/LabelObject.hpp"

namespace nastya::typesystem {

LabelObject::LabelObject(std::string value) : GenericObject(ObjectType::Label), m_value(std::move(value))
{
}

std::string LabelObject::getValue() const
{
    return m_value;
}

IObject* LabelObject::clone() const
{
    return new LabelObject(*this);
}

std::string LabelObject::toString() const
{
    return m_value;
}
std::string LabelObject::info() const
{
    std::stringstream ss;
    ss << "Label => " << toString();
    return ss.str();
}

}  // namespace nastya::typesystem
