//
// Created by caedus on 12.12.2020.
//

#pragma once

#include "LispExpression/Interface/IObjectStorage.hpp"

#include <memory>

namespace nastya::lisp {

class ObjectStorage : public IObjectStorage {
public:
    ObjectStorage();
    explicit ObjectStorage(std::unique_ptr<IObject> object);
    ObjectStorage(const ObjectStorage& rhs);
    ObjectStorage(ObjectStorage&& rhs);

    ObjectStorage& operator=(const ObjectStorage& rhs);
    ObjectStorage& operator=(ObjectStorage&& rhs);

    ObjectType getType() const override;
    IObject& getRawObject() const override;
private:
    std::unique_ptr<IObject> m_object;
};
}
