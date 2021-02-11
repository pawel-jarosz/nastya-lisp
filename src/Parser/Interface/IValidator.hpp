//
// Created by caedus on 11.02.2021.
//

#pragma once

#include "Parser/Types/Token.hpp"
#include <optional>

namespace nastya::parser {

struct ParsingContext {
    size_t end_position;
};

class IValidator
{
public:
    ~IValidator() = default;
    virtual std::optional<Token> validate(const std::string& value, ParsingContext& context) const = 0;
};

}  // namespace nastya::parser
