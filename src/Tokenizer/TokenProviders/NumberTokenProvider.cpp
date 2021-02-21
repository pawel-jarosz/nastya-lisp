//
// Created by caedus on 09.02.2021.
//

#include <regex>

#include "Tokenizer/TokenProviders/NumberTokenProvider.hpp"

namespace nastya::tokens {

void NumberTokenProvider::addType(std::string regex, NumberFactory factory)
{
    m_factories.emplace_back(std::pair(regex, std::move(factory)));
}

std::optional<Token> NumberTokenProvider::getTokenIfAvailable(const std::string& value, ParsingContext&) const
{
    for (const auto& [type_regex, factory] : m_factories)
    {
        std::regex regex_object(type_regex);
        std::smatch m;
        if (std::regex_match(value, m, regex_object))
        {
            const auto token = factory(value);
            if (token)
            {
                return token.value();
            }
        }
    }
    return {};
}
std::unique_ptr<ITokenProvider> NumberTokenProvider::create()
{
    auto result = std::make_unique<NumberTokenProvider>();
    result->addType(FLOATING_REGEX, parse_float);
    result->addType(INTEGER_REGEX, parse_integer);
    return std::unique_ptr<ITokenProvider>(result.release());
}

std::optional<Token> parse_float(const std::string& value)
{
    const auto result = std::stof(value);
    return {Token{TokenType::Floating, result}};
}

std::optional<Token> parse_integer(const std::string& value)
{
    const auto result = std::stoi(value);
    return {Token{TokenType::Integer, result}};
}

}  // namespace nastya::tokens
