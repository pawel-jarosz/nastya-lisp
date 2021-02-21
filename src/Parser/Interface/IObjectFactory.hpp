//
// Created by caedus on 13.12.2020.
//

#pragma once

#include <functional>

#include "Tokenizer/Types/Token.hpp"
#include "TypeSystem/Interface/IObject.hpp"

namespace nastya::parser {

using FactoryMethod = std::function<typesystem::IObject*(const tokens::Token& t)>;

class IObjectFactory
{
public:
    virtual ~IObjectFactory() = default;
    virtual typesystem::IObject* create(const tokens::Token& t) const = 0;
    virtual void registerToken(const tokens::TokenType type, FactoryMethod factory) = 0;
};
}  // namespace nastya::parser
