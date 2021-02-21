//
// Created by caedus on 13.12.2020.
//

#pragma once

#include <functional>

#include "Parser/Interface/IObjectFactory.hpp"
#include "Tokenizer/Types/Token.hpp"

namespace nastya::parser {
class ObjectFactory : public IObjectFactory
{
public:
    ObjectFactory() = default;
    typesystem::IObject* create(const tokens::Token& t) const override;
    void registerToken(const tokens::TokenType type, FactoryMethod factory) override;

private:
    mutable std::map<tokens::TokenType, std::function<typesystem::IObject*(const tokens::Token& t)>> m_factories;
};

}  // namespace nastya::parser
