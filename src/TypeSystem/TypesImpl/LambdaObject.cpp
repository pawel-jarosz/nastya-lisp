//
// Created by caedus on 13.02.2021.
//

#include "TypeSystem/Types/LambdaObject.hpp"
#include <sstream>

namespace nastya::lisp::typesystem {

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

}

