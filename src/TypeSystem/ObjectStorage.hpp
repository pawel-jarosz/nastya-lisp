//
// Created by caedus on 12.12.2020.
//

#pragma once

#include <memory>
#include <ostream>

#include "TypeSystem/Interface/IObjectStorage.hpp"

namespace nastya::lisp {

class ObjectStorage : public IObjectStorage
{
public:
    ObjectStorage() = default;
    explicit ObjectStorage(std::unique_ptr<IObject> object);
    ObjectStorage(const ObjectStorage& rhs);
    ObjectStorage(ObjectStorage&& rhs);

    ObjectStorage& operator=(const ObjectStorage& rhs);
    ObjectStorage& operator=(ObjectStorage&& rhs);

    ObjectType getType() const override;
    IObject& getRawObject() const override;
    std::string toString() const;

private:
    std::unique_ptr<IObject> m_object;
};
}  // namespace nastya::lisp
