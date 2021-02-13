//
// Created by caedus on 13.02.2021.
//

#include "TypeSystem/Types/ListObject.hpp"
#include <sstream>
namespace nastya::lisp::typesystem {

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


}
