//
// Created by caedus on 12.02.2021.
//

#include "Parser/SimpleTokenizers/ReservedCharacterValidator.hpp"

#include <iostream>

namespace nastya::parser {

std::optional<Token> ReservedCharacterValidator::validate(const std::string& value, ParsingContext& context) const
{
    context.end_position = context.start_position + 1;
    switch (value[context.start_position])
    {
        case '(':
            return {Token{TokenType::S_expr_begin, {}}};
        case ')':
            return {Token{TokenType::S_expr_end, {}}};
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '%':
            if (context.start_position < value.size() and isblank(value[context.start_position + 1])) {
                return Token{TokenType::Label, std::string{value[context.start_position]}};
            }
            break;
        case '\'':
            return {Token{TokenType::Quote, {}}};
    }
    return {};
}

std::unique_ptr<IValidator> ReservedCharacterValidator::create()
{
    auto result = std::make_unique<ReservedCharacterValidator>();
    return std::unique_ptr<IValidator>(result.release());
}

}
