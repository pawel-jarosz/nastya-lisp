//
// Created by caedus on 13.12.2020.
//

#include "LispExpression/ObjectFactory.hpp"

namespace nastya::lisp {

void ObjectFactory::registerToken(const parser::TokenType type,
                                  FactoryMethod factory)
{
    m_factories[type] = factory;
}

IObject* ObjectFactory::create(const parser::Token& t) const
{
    // TODO: Add error case!
    return m_factories[t.type](t);
}

}  // namespace nastya::lisp