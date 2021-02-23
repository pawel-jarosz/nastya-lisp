//
// Created by caedus on 13.12.2020.
//

#include "ObjectStorage.hpp"
#include "ObjectStorageException.hpp"

namespace nastya::typesystem {

ObjectStorage::ObjectStorage(std::unique_ptr<IObject> object) : m_object{std::move(object)}
{
}

ObjectStorage::ObjectStorage(const ObjectStorage& rhs) : m_object(rhs.getRawObject().clone())
{
}

ObjectStorage::ObjectStorage(ObjectStorage&& rhs) : m_object{std::move(rhs.m_object)}
{
}

ObjectStorage& ObjectStorage::operator=(const ObjectStorage& rhs)
{
    m_object.reset(rhs.m_object->clone());
    return *this;
}

ObjectStorage& ObjectStorage::operator=(ObjectStorage&& rhs)
{
    m_object = std::move(rhs.m_object);
    return *this;
}

ObjectType ObjectStorage::getType() const
{
    if (not m_object)
    {
        BUT_THROW(ObjectStorageException, "Object is not initialized");
    }
    return m_object->getType();
}

IObject& ObjectStorage::getRawObject() const
{
    if (not m_object)
    {
        BUT_THROW(ObjectStorageException, "Object is not initialized");
    }
    return *m_object;
}

std::string ObjectStorage::toString() const
{
    if (not m_object)
    {
        BUT_THROW(ObjectStorageException, "Object is not initialized");
    }
    return m_object->toString();
}

}  // namespace nastya::typesystem