//
// Created by caedus on 15.12.2020.
//

#include <sstream>
#include <type_traits>

#include "LispExpression/Testing/ListBuilder.hpp"
#include "TypeSystem/Types/LabelObject.hpp"
#include "TypeSystem/Types/ListObject.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "TypeSystem/Types/StringObject.hpp"
#include "TypeSystem/Types/BooleanObject.hpp"

namespace nastya::lisp::testing {

template <typename T>
std::unique_ptr<IObject> make_unique_object(T* value)
{
    static_assert(std::is_base_of<IObject, T>::value, "Invalid type");
    return std::unique_ptr<IObject>(value);
}

ListBuilder::ListBuilder(ListBuilder* builder) : m_parent{builder}
{
}

ListBuilder& ListBuilder::closeList()
{
    if (m_parent)
    {
        return m_parent->addList(m_objects);
    }
    // TODO: Add exception type;
    throw std::logic_error("Wrong closing!");
}

ListBuilder& ListBuilder::openList()
{
    m_child = std::make_unique<ListBuilder>(this);
    return *m_child;
}

ListBuilder& ListBuilder::addList(const std::vector<ObjectStorage>& value)
{
    auto temp = make_unique_object(new typesystem::ListObject(value));
    m_objects.emplace_back(ObjectStorage(std::move(temp)));
    return *this;
}

ListBuilder& ListBuilder::addLabel(const std::string& value)
{
    auto temp = make_unique_object(new typesystem::LabelObject(value));
    m_objects.emplace_back(ObjectStorage(std::move(temp)));
    return *this;
}

ListBuilder& ListBuilder::addString(const std::string& value)
{
    auto temp = make_unique_object(new typesystem::StringObject(value));
    m_objects.emplace_back(ObjectStorage(std::move(temp)));
    return *this;
}

ListBuilder& ListBuilder::addNumber(int value)
{
    auto temp = make_unique_object(new typesystem::NumberObject(value));
    m_objects.emplace_back(ObjectStorage(std::move(temp)));
    return *this;
}

ListBuilder& ListBuilder::addNumber(float value)
{
    auto temp = make_unique_object(new typesystem::NumberObject(value));
    m_objects.emplace_back(ObjectStorage(std::move(temp)));
    return *this;
}
ObjectStorage ListBuilder::build()
{
    auto temp = make_unique_object(new typesystem::ListObject(m_objects));
    return ObjectStorage(std::move(temp));
}
ListBuilder& ListBuilder::addBoolean(bool value)
{
    auto temp = make_unique_object(new typesystem::BooleanObject(value));
    m_objects.emplace_back(ObjectStorage(std::move(temp)));
    return *this;
}

}  // namespace nastya::lisp::testing
