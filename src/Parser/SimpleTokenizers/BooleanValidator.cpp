//
// Created by caedus on 09.02.2021.
//

#include "Parser/SimpleTokenizers/BooleanValidator.hpp"

namespace nastya::parser {

BooleanValidator::BooleanValidator(std::string true_string, std::string false_string)
: m_true_value{std::move(true_string)}
, m_false_value{std::move(false_string)}
{
}

std::optional<Token> BooleanValidator::validate(const std::string& value, ParsingContext&) const
{
    if (value == m_true_value or value == m_false_value) {
        return Token { TokenType::Boolean, (value.compare(m_true_value) == 0)};
    }
    return {};
}
std::unique_ptr<IValidator> BooleanValidator::create()
{
    auto result = std::make_unique<BooleanValidator>(TRUE_VALUE, FALSE_VALUE);
    return std::unique_ptr<IValidator>(result.release());
}

}
