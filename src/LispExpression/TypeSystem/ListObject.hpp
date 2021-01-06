//
// Created by caedus on 12.12.2020.
//

#pragma once

#include <vector>

#include "LispExpression/ObjectStorage.hpp"
#include "LispExpression/TypeSystem/GenericObject.hpp"

// TODO: Implement after ObjectStorage

namespace nastya::lisp::typesystem {
class ListObject : public GenericObject
{
public:
    ListObject();
    explicit ListObject(std::vector<ObjectStorage> content);
    ListObject(ListObject&) = default;
    ListObject(ListObject&&) = default;
    ListObject& operator=(const ListObject&) = default;
    ListObject& operator=(ListObject&&) = default;
    bool isEmpty() const { return m_content.empty(); }
    size_t getSize() const { return m_content.size(); }
    const std::vector<ObjectStorage>& getContent() const;
    IObject* clone() const override;
    std::string toString() const override;
    std::string info() const override;

private:
    std::vector<ObjectStorage> m_content;
};
}  // namespace nastya::lisp::typesystem
