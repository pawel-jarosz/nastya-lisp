//
// Created by caedus on 11.02.2021.
//

#pragma once

#include "Parser/Types/Token.hpp"
#include "Parser/Types/ParsingContext.hpp"
#include <optional>

namespace nastya::parser {

class IValidator
{
public:
    ~IValidator() = default;
    virtual std::optional<Token> validate(const std::string& value, ParsingContext& context) const = 0;
};

}  // namespace nastya::parser
