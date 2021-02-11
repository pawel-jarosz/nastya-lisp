//
// Created by caedus on 11.02.2021.
//

#pragma once

#include "Parser/Types/Token.hpp"
#include <optional>

namespace nastya::parser {

struct ParsingContext {
    const size_t start_position;
    size_t end_position;

    ParsingContext(size_t start_pos) : start_position{start_pos}{};
};

class IValidator
{
public:
    ~IValidator() = default;
    virtual std::optional<Token> validate(const std::string& value, ParsingContext& context) const = 0;
};

}  // namespace nastya::parser
