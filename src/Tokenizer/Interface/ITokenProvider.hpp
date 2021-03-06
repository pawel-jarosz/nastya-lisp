//
// Created by caedus on 11.02.2021.
//

#pragma once

#include "Tokenizer/Types/Token.hpp"
#include "Tokenizer/Types/ParsingContext.hpp"
#include <optional>

namespace nastya::tokens {

class ITokenProvider
{
public:
    ~ITokenProvider() = default;
    virtual std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const = 0;
};

}  // namespace nastya::tokens
