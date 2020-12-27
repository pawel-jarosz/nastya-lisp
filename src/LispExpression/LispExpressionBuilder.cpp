//
// Created by caedus on 15.12.2020.
//

#include "LispExpression/LispExpressionBuilder.hpp"

#include <functional>
#include <map>
#include <stack>
#include <vector>

#include "LispExpression/Interface/IObjectFactory.hpp"
#include "LispExpression/LispExpressionBuilder.hpp"
#include "LispExpression/TypeSystem/ListObject.hpp"
#include "LispExpression/LispExpressionException.hpp"

namespace nastya::lisp {

class LispExpressionBuilder::LispExpressionBuilderImpl
{
public:
    LispExpressionBuilderImpl(IObjectFactory& object_factory);
    void addToken(const parser::Token& t);
    ObjectStorage build();

private:
    void openList();
    void closeList();
    void addGenericObject(const parser::Token& t);

    IObjectFactory& m_factory;
    std::stack<std::vector<ObjectStorage>> m_stack;
    ObjectStorage m_result;
};

LispExpressionBuilder::LispExpressionBuilderImpl::LispExpressionBuilderImpl(
    IObjectFactory& object_factory)
    : m_factory{object_factory}
{
}

void LispExpressionBuilder::LispExpressionBuilderImpl::addToken(
    const parser::Token& t)
{
    switch (t.type)
    {
        case parser::TokenType::S_expr_begin:
            openList();
            break;
        case parser::TokenType::S_expr_end:
            closeList();
            break;
        default:
            addGenericObject(t);
    }
}

ObjectStorage LispExpressionBuilder::LispExpressionBuilderImpl::build()
{
    return m_result;
}

void LispExpressionBuilder::LispExpressionBuilderImpl::openList()
{
    m_stack.push(std::vector<ObjectStorage>());
}

void LispExpressionBuilder::LispExpressionBuilderImpl::closeList()
{
    if (m_stack.empty()) {
        BUT_THROW(LispExpressionException, "Stack is empty");
    }
    std::unique_ptr<IObject> top_object(
        new typesystem::ListObject(m_stack.top())
    );
    m_stack.pop();
    ObjectStorage temp(std::move(top_object));
    if (not m_stack.empty())
    {
        m_stack.top().emplace_back(std::move(temp));
    }
    else {
        m_result = temp;
    }
}

void LispExpressionBuilder::LispExpressionBuilderImpl::addGenericObject(
    const parser::Token& t)
{
    std::unique_ptr<IObject> temp(m_factory.create(t));
    ObjectStorage object(std::move(temp));
    if (not m_stack.empty()) {
        m_stack.top().emplace_back(std::move(object));
    }
    else {
        m_result = object;
    }
}

LispExpressionBuilder::LispExpressionBuilder(parser::IParser& parser,
                                             IObjectFactory& object_factory)
    : m_parser{parser}
    , m_object_factory{object_factory}
    , m_impl(new LispExpressionBuilder::LispExpressionBuilderImpl(object_factory))
{
}

LispExpressionBuilder::~LispExpressionBuilder()
{
}

ObjectStorage LispExpressionBuilder::build()
{
    parser::Token t;
    while ((t = m_parser.getToken()).type != parser::TokenType::Eof)
    {
        m_impl->addToken(t);
    }
    return m_impl->build();
}

}  // namespace nastya::lisp
