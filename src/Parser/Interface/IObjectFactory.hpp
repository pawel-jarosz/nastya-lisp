//
// Created by caedus on 13.12.2020.
//

#pragma once

#include <functional>

#include "Tokenizer/Types/Token.hpp"
#include "TypeSystem/Interface/IObject.hpp"

namespace nastya::lisp {

using FactoryMethod = std::function<IObject*(const parser::Token& t)>;

class IObjectFactory
{
public:
    virtual ~IObjectFactory() = default;
    virtual IObject* create(const parser::Token& t) const = 0;
    virtual void registerToken(const parser::TokenType type, FactoryMethod factory) = 0;
};
}  // namespace nastya::lisp
