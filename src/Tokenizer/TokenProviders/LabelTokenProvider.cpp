//
// Created by caedus on 11.02.2021.
//

#include <regex>

#include "Tokenizer/TokenProviders/LabelTokenProvider.hpp"

namespace nastya::tokens {

LabelTokenProvider::LabelTokenProvider(std::string label_regex) : m_label_regex{std::move(label_regex)}
{
}

std::optional<Token> LabelTokenProvider::getTokenIfAvailable(const std::string& value, ParsingContext&) const
{
    std::regex regex_object(m_label_regex);
    std::smatch m;
    if (std::regex_match(value, m, regex_object))
    {
        return Token{TokenType::Label, value};
    }
    return {};
}
std::unique_ptr<ITokenProvider> LabelTokenProvider::create()
{
    auto result = std::make_unique<LabelTokenProvider>(LABEL_REGEX);
    return std::unique_ptr<ITokenProvider>(result.release());
}

}  // namespace nastya::tokens
