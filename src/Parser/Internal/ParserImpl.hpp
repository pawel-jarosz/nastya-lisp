//
// Created by caedus on 14.02.2021.
//

#pragma once

#include <stack>

#include "Parser/Interface/IObjectFactory.hpp"
#include "TypeSystem/ObjectStorage.hpp"

namespace nastya::parser {
struct ParserImpl
{
    ParserImpl(IObjectFactory& object_factory);
    void dispatch(const tokens::Token& t);
    typesystem::ObjectStorage build();

    void openList();
    void closeList();
    void addGenericObject(const tokens::Token& t);
    void enableQuotation();
    void disableQuotation();

    IObjectFactory& m_factory;
    std::stack<std::vector<typesystem::ObjectStorage>> m_stack;
    std::stack<size_t> m_quotation_stack;
    typesystem::ObjectStorage m_result;
};

}
