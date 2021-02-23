//
// Created by caedus on 13.12.2020.
//

#include "Parser/LispExpressionException.hpp"
#include "Parser/ObjectFactory.hpp"

namespace nastya::parser {

void ObjectFactory::registerToken(const tokens::TokenType type, FactoryMethod factory)
{
    m_factories[type] = factory;
}

typesystem::IObject* ObjectFactory::create(const tokens::Token& t) const
{
    if (m_factories.find(t.type) == m_factories.end())
    {
        BUT_THROW(LispExpressionException, "Factory is not registered for token");
    }
    return m_factories[t.type](t);
}

}  // namespace nastya::parser