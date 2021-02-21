//
// Created by caedus on 14.02.2021.
//

#include "Parser/Internal/ParserImpl.hpp"
#include "Parser/LispExpressionException.hpp"
#include "TypeSystem/Types/ListObject.hpp"

namespace nastya::parser {

ParserImpl::ParserImpl(IObjectFactory& object_factory) : m_factory{object_factory}
{
}

void ParserImpl::addToken(const tokens::Token& t)
{
    switch (t.type)
    {
        case tokens::TokenType::S_expr_begin:
            openList();
            break;
        case tokens::TokenType::S_expr_end:
            disableQuotation();
            closeList();
            break;
        case tokens::TokenType::Quote:
            enableQuotation();
            break;
        default:
            addGenericObject(t);
    }
}

typesystem::ObjectStorage ParserImpl::build()
{
    return m_result;
}

void ParserImpl::enableQuotation()
{
    tokens::Token label_token{tokens::TokenType::Label, std::string("Quote")};
    openList();
    addGenericObject(label_token);
    m_quotation_stack.push(m_stack.size());
}

void ParserImpl::disableQuotation()
{
    if (m_quotation_stack.empty())
    {
        return;
    }
    if (m_stack.size() != m_quotation_stack.top() + 1)
    {
        return;
    }
    closeList();
}

void ParserImpl::openList()
{
    m_stack.push(std::vector<typesystem::ObjectStorage>());
}

void ParserImpl::closeList()
{
    if (m_stack.empty())
    {
        BUT_THROW(LispExpressionException, "Stack is empty");
    }
    std::unique_ptr<typesystem::IObject> top_object(new typesystem::ListObject(m_stack.top()));
    m_stack.pop();
    typesystem::ObjectStorage temp(std::move(top_object));
    if (not m_stack.empty())
    {
        m_stack.top().emplace_back(std::move(temp));
    }
    else
    {
        m_result = temp;
    }
}

void ParserImpl::addGenericObject(const tokens::Token& t)
{
    std::unique_ptr<typesystem::IObject> temp(m_factory.create(t));
    typesystem::ObjectStorage object(std::move(temp));
    if (not m_stack.empty())
    {
        m_stack.top().emplace_back(std::move(object));
    }
    else
    {
        m_result = object;
    }
}

}  // namespace nastya::parser
