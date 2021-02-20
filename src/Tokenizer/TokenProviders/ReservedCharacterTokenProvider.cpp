//
// Created by caedus on 12.02.2021.
//

#include <iostream>

#include "Tokenizer/TokenProviders/ReservedCharacterTokenProvider.hpp"

namespace nastya::tokens {

std::optional<Token> ReservedCharacterTokenProvider::getTokenIfAvailable(const std::string& value, ParsingContext& context) const
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
            if (context.start_position + 1 == value.size()
                or (context.start_position + 1 < value.size() and 
                    isblank(value[context.start_position + 1]))) {
                return Token{TokenType::Label, std::string{value[context.start_position]}};
            }
            break;
        case '\'':
            return {Token{TokenType::Quote, {}}};
    }
    return {};
}

std::unique_ptr<ITokenProvider> ReservedCharacterTokenProvider::create()
{
    auto result = std::make_unique<ReservedCharacterTokenProvider>();
    return std::unique_ptr<ITokenProvider>(result.release());
}

}
