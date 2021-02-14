//
// Created by caedus on 15.12.2020.
//

#include <functional>
#include <map>
#include <stack>
#include <vector>

#include "Parser/Interface/IObjectFactory.hpp"
#include "Parser/LispExpressionBuilder.hpp"
#include "Parser/LispExpressionException.hpp"
#include "TypeSystem/Types/ListObject.hpp"

namespace nastya::lisp {

class LispExpressionBuilder::LispExpressionBuilderImpl
{
public:
    LispExpressionBuilderImpl(IObjectFactory& object_factory);
    void addToken(const tokens::Token& t);
    typesystem::ObjectStorage build();

private:
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

LispExpressionBuilder::LispExpressionBuilderImpl::LispExpressionBuilderImpl(IObjectFactory& object_factory)
: m_factory{object_factory}
{
}

void LispExpressionBuilder::LispExpressionBuilderImpl::addToken(const tokens::Token& t)
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

typesystem::ObjectStorage LispExpressionBuilder::LispExpressionBuilderImpl::build()
{
    return m_result;
}

void LispExpressionBuilder::LispExpressionBuilderImpl::enableQuotation()
{
    tokens::Token label_token{tokens::TokenType::Label, std::string("Quote")};
    openList();
    addGenericObject(label_token);
    m_quotation_stack.push(m_stack.size());
}

void LispExpressionBuilder::LispExpressionBuilderImpl::disableQuotation()
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

void LispExpressionBuilder::LispExpressionBuilderImpl::openList()
{
    m_stack.push(std::vector<typesystem::ObjectStorage>());
}

void LispExpressionBuilder::LispExpressionBuilderImpl::closeList()
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

void LispExpressionBuilder::LispExpressionBuilderImpl::addGenericObject(const tokens::Token& t)
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

LispExpressionBuilder::LispExpressionBuilder(tokens::ITokenizer& parser, IObjectFactory& object_factory)
: m_parser{parser}
, m_object_factory{object_factory}
, m_impl(new LispExpressionBuilder::LispExpressionBuilderImpl(object_factory))
{
}

LispExpressionBuilder::~LispExpressionBuilder()
{
}

typesystem::ObjectStorage LispExpressionBuilder::build()
{
    tokens::Token t;
    while ((t = m_parser.getToken()).type != tokens::TokenType::Eof)
    {
        m_impl->addToken(t);
    }
    return m_impl->build();
}
void LispExpressionBuilder::reset()
{
    m_impl.reset(new LispExpressionBuilder::LispExpressionBuilderImpl(m_object_factory));
}

}  // namespace nastya::lisp
