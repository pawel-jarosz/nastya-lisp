//
// Created by caedus on 13.12.2020.
//

#pragma once

#include "LispExpression/Interface/IObjectFactory.hpp"
#include "Parser/Types/Token.hpp"

#include <functional>

namespace nastya::lisp {
class ObjectFactory : public IObjectFactory {
public:
    ObjectFactory() = default;
    IObject* create(const parser::Token& t) const override;
    void registerToken(const parser::TokenType type, FactoryMethod factory) override;
private:
    mutable std::map<parser::TokenType, std::function<IObject*(const parser::Token& t)>> m_factories;
};

}
