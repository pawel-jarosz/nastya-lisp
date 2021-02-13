//
// Created by caedus on 13.02.2021.
//

#include "TypeSystem/Types/StringObject.hpp"
#include "TypeSystem/Types/TypeSystemError.hpp"

namespace nastya::lisp::typesystem {

StringObject::StringObject(std::string value) : GenericObject(ObjectType::String), m_value(std::move(value))
{
}

std::string StringObject::getValue() const
{
    return m_value;
}

IObject* StringObject::clone() const
{
    return new StringObject(*this);
}

std::string StringObject::toString() const
{
    std::stringstream ss;
    ss << "\"" << m_value << "\"";
    return ss.str();
}
std::string StringObject::info() const
{
    std::stringstream ss;
    ss << "String => " << toString();
    return ss.str();
}
int StringObject::compare(const IObject& rhs) const
{
    if (rhs.getType() != ObjectType::String) {
        BUT_THROW(TypeSystemError, "Given arguments are not comparable");
    }
    const auto casted_rhs = dynamic_cast<const StringObject&>(rhs);
    const auto rhs_text = casted_rhs.getValue();
    if (m_value < rhs_text) {
        return -1;
    }
    else if (m_value == rhs_text) {
        return 0;
    }
    else {
        return 1;
    }
}


}
