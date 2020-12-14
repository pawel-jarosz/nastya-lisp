//
// Created by caedus on 12.12.2020.
//

#pragma once

#include "LispExpression/TypeSystem/GenericObject.hpp"
#include "LispExpression/ObjectStorage.hpp"

#include <vector>

// TODO: Implement after ObjectStorage

namespace nastya::lisp::typesystem {
class ListObject : public GenericObject {
public:
    ListObject();
    explicit ListObject(std::vector<ObjectStorage> content);
    ListObject(ListObject&) = default;
    ListObject(ListObject&&) = default;
    ListObject& operator=(const ListObject&) = default;
    ListObject& operator=(ListObject&&) = default;
    const std::vector<ObjectStorage>& getContent() const;
    IObject* clone() const;
private:
    std::vector<ObjectStorage> m_content;
};
}
