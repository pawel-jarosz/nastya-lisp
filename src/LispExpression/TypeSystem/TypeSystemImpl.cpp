#include <utility>
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "LispExpression/TypeSystem/BooleanObject.hpp"
#include "LispExpression/TypeSystem/LabelObject.hpp"
#include "LispExpression/TypeSystem/NumberObject.hpp"
#include "LispExpression/TypeSystem/StringObject.hpp"

namespace nastya::lisp::typesystem {

GenericObject::GenericObject(ObjectType type) : m_type{type}
{
}

ObjectType GenericObject::getType() const
{
    return m_type;
}

BooleanObject::BooleanObject(bool value)
: GenericObject(ObjectType::Boolean), m_value{value}
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

LabelObject::LabelObject(std::string value)
: GenericObject(ObjectType::Label), m_value(std::move(value))
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

StringObject::StringObject(std::string value)
: GenericObject(ObjectType::String), m_value(std::move(value))
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

NumberObject::NumberObject() : NumberObject(0)
{
}

NumberObject::NumberObject(int value)
: GenericObject(ObjectType::Number)
, m_int_value(value)
, m_type{NumberType::Integer}
{
}

NumberObject::NumberObject(float value)
: GenericObject(ObjectType::Number)
, m_float_value(value)
, m_type{NumberType::Floating}
{
}

NumberObject::NumberObject(const NumberObject& rhs)
: GenericObject(ObjectType::Number), m_type{NumberType::Integer}
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

NumberObject::NumberObject(NumberObject&& rhs)
: GenericObject(ObjectType::Number), m_type{NumberType::Integer}
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
    // TODO: add exception if integer
    return m_float_value;
}

int NumberObject::getInteger() const
{
    // TODO: add exception if floating
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

ListObject::ListObject(std::vector<ObjectStorage> content)
: GenericObject(ObjectType::List), m_content{std::move(content)}
{
}

ListObject::ListObject() : GenericObject(ObjectType::List)
{
}

const std::vector<ObjectStorage>& ListObject::getContent() const
{
    return m_content;
}

IObject* ListObject::clone() const
{
    return new ListObject(getContent());
}

}  // namespace nastya::lisp::typesystem
