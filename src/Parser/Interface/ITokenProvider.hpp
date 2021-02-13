//
// Created by caedus on 11.02.2021.
//

#pragma once

#include "Parser/Types/Token.hpp"
#include "Parser/Types/ParsingContext.hpp"
#include <optional>

namespace nastya::parser {

class ITokenProvider
{
public:
    ~ITokenProvider() = default;
    virtual std::optional<Token> getTokenIfAvailable(const std::string& value, ParsingContext& context) const = 0;
};

}  // namespace nastya::parser
