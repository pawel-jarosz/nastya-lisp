//
// Created by caedus on 11.02.2021.
//

#include "Parser/SimpleTokenizers/LabelValidator.hpp"
#include <regex>

namespace nastya::parser {

LabelValidator::LabelValidator(std::string label_regex)
: m_label_regex{std::move(label_regex)}
{
}

std::optional<Token> LabelValidator::validate(const std::string& value, ParsingContext&) const
{
    std::regex regex_object(m_label_regex);
    std::smatch m;
    if (std::regex_match(value, m, regex_object))
    {
        return Token{TokenType::Label, value};
    }
    return {};
}
std::unique_ptr<IValidator> LabelValidator::create()
{
    auto result = std::make_unique<LabelValidator>(LABEL_REGEX);
    return std::unique_ptr<IValidator>(result.release());
}

}
