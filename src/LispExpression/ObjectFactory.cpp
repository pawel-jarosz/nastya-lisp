//
// Created by caedus on 13.12.2020.
//

#include <iostream>

#include "LispExpression/LispExpressionException.hpp"
#include "LispExpression/ObjectFactory.hpp"

namespace nastya::lisp {

void ObjectFactory::registerToken(const parser::TokenType type, FactoryMethod factory)
{
    m_factories[type] = factory;
}

IObject* ObjectFactory::create(const parser::Token& t) const
{
    if (m_factories.find(t.type) == m_factories.end())
    {
        std::cout << "TokenType: " << t.type << std::endl;
        BUT_THROW(LispExpressionException, "Factory is not registered for token");
    }
    return m_factories[t.type](t);
}

}  // namespace nastya::lisp