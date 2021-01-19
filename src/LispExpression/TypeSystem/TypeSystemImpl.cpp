#include <sstream>
#include <utility>

#include "LispExpression/TypeSystem/GenericObject.hpp"
#include "LispExpression/TypeSystem/BooleanObject.hpp"
#include "LispExpression/TypeSystem/LabelObject.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "LispExpression/TypeSystem/NumberObject.hpp"
#include "LispExpression/TypeSystem/StringObject.hpp"
#include "LispExpression/TypeSystem/TypeSystemError.hpp"
#include "LispExpression/TypeSystem/LambdaObject.hpp"

namespace nastya::lisp::typesystem {

template <typename T>
std::string toString(const T& value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template <>
std::string toString(const bool& value)
{
    if (value)
    {
        return "#true";
    }
    else
        return "#false";
}

GenericObject::GenericObject(ObjectType type) : m_type{type}
{
}

ObjectType GenericObject::getType() const
{
    return m_type;
}
bool GenericObject::equal(const IObject& object) const
{
    return (toString() == object.toString());
}

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
    return nastya::lisp::typesystem::toString(m_value);
}
std::string BooleanObject::info() const
{
    std::stringstream ss;
    ss << "Boolean => " << toString();
    return ss.str();
}

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
    return nastya::lisp::typesystem::toString(m_value);
}
std::string LabelObject::info() const
{
    std::stringstream ss;
    ss << "Label => " << toString();
    return ss.str();
}

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
    ss << "\"" << nastya::lisp::typesystem::toString(m_value) << "\"";
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
    if (m_type == NumberType::Integer) {
        BUT_THROW(TypeSystemError, "Number is floating");
    }
    return m_float_value;
}

int NumberObject::getInteger() const
{
    if (m_type == NumberType::Floating) {
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
    if (m_type == NumberType::Integer)
    {
        return nastya::lisp::typesystem::toString(m_int_value);
    }
    return nastya::lisp::typesystem::toString(m_float_value);
}
std::string NumberObject::info() const
{
    std::stringstream ss;
    if (getNumberType() == lisp::NumberType::Floating)
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

int compare_int(const int lhs, const int rhs) {
    if (lhs < rhs) {
        return -1;
    }
    else if (lhs == rhs) {
        return 0;
    }
    else {
        return 1;
    }
}

int compare_float(const float lhs, const float rhs) {
    if (lhs < rhs) {
        return -1;
    }
    else if (lhs == rhs) {
        return 0;
    }
    else {
        return 1;
    }
}

int compare_number(const int value, const NumberObject& rhs) {
    if(rhs.getNumberType() == NumberType::Integer) {
        return compare_int(value, rhs.getInteger());
    }
    return compare_float(value,rhs.getFloating());
}

int compare_number(const float value, const NumberObject& rhs) {
    if(rhs.getNumberType() == NumberType::Floating) {
        return compare_int(value, rhs.getFloating());
    }
    return compare_float(value, rhs.getInteger());
}

int NumberObject::compare(const IObject& rhs) const
{
    if (rhs.getType() != ObjectType::Number) {
        BUT_THROW(TypeSystemError, "Given arguments are not comparable");
    }
    auto casted_rhs = dynamic_cast<const NumberObject&>(rhs);
    if (m_type == NumberType::Integer) {
        return compare_number(m_int_value, casted_rhs);
    }
    return compare_number(m_float_value, casted_rhs);
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

std::string ListObject::toString() const
{
    std::stringstream ss;
    if (m_content.size() == 0)
    {
        return "()";
    }
    ss << "(" << m_content[0].getRawObject().toString();
    for (int i = 1; i < m_content.size(); i++)
    {
        ss << " " << m_content[i].toString();
    }
    ss << ")";
    return ss.str();
}
std::string ListObject::info() const
{
    std::stringstream ss;
    ss << "List => " << toString();
    return ss.str();
}

LambdaObject::LambdaObject(const ListObject& argumentsList, const ListObject& command)
: m_arguments(argumentsList.getContent())
, m_command(command.getContent())
{
}

LambdaObject::LambdaObject(const LambdaObject& rhs)
: m_arguments{rhs.getArgumentsList().getContent()}
, m_command{rhs.getCommand().getContent()}
{
}

LambdaObject::LambdaObject(LambdaObject&& rhs)
{
    m_arguments = std::move(rhs.m_arguments);
    m_command = std::move(rhs.m_command);
}

LambdaObject& LambdaObject::operator=(const LambdaObject& rhs)
{
    m_arguments = rhs.m_arguments;
    m_command = rhs.m_command;
    return *this;
}
LambdaObject& LambdaObject::operator=(LambdaObject&& rhs)
{
    m_arguments = std::move(rhs.m_arguments);
    m_command = std::move(rhs.m_command);
    return *this;
}

ObjectType LambdaObject::getType() const
{
    return ObjectType::Lambda;
}

IObject* LambdaObject::clone() const
{
    return new LambdaObject(m_arguments, m_command);
}

std::string LambdaObject::toString() const
{
    std::stringstream ss;
    ss << "Lambda => args:" << m_arguments.toString();
    return std::string();
}

std::string LambdaObject::info() const
{
    return toString();
}
const ListObject& LambdaObject::getArgumentsList() const
{
    return m_arguments;
}

const ListObject& LambdaObject::getCommand() const
{
    return m_command;
}

}  // namespace nastya::lisp::typesystem
