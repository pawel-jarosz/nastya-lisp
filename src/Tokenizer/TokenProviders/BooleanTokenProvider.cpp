//
// Created by caedus on 09.02.2021.
//

#include "Tokenizer/TokenProviders/BooleanTokenProvider.hpp"

namespace nastya::tokens {

BooleanTokenProvider::BooleanTokenProvider(std::string true_string, std::string false_string)
: m_true_value{std::move(true_string)}
, m_false_value{std::move(false_string)}
{
}

std::optional<Token> BooleanTokenProvider::getTokenIfAvailable(const std::string& value, ParsingContext&) const
{
    if (value == m_true_value or value == m_false_value) {
        return Token { TokenType::Boolean, (value.compare(m_true_value) == 0)};
    }
    return {};
}
std::unique_ptr<ITokenProvider> BooleanTokenProvider::create()
{
    auto result = std::make_unique<BooleanTokenProvider>(TRUE_VALUE, FALSE_VALUE);
    return std::unique_ptr<ITokenProvider>(result.release());
}

}
