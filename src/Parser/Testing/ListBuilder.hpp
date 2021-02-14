//
// Created by caedus on 15.12.2020.
//

#pragma once

#include <memory>
#include <vector>

#include <TypeSystem/ObjectStorage.hpp>

namespace nastya::lisp::testing {

// TODO: Add boolean
class ListBuilder
{
public:
    ListBuilder() = default;
    explicit ListBuilder(ListBuilder* parent);
    ListBuilder& openList();
    ListBuilder& addList(const std::vector<typesystem::ObjectStorage>& value);
    ListBuilder& addBoolean(bool value);
    ListBuilder& addNumber(float value);
    ListBuilder& addNumber(int value);
    ListBuilder& addString(const std::string& value);
    ListBuilder& addLabel(const std::string& value);
    ListBuilder& closeList();
    typesystem::ObjectStorage build();

private:
    ListBuilder* m_parent;
    std::unique_ptr<ListBuilder> m_child;
    std::vector<typesystem::ObjectStorage> m_objects;
};

}  // namespace nastya::lisp::testing