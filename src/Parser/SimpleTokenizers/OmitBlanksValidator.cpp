//
// Created by caedus on 12.02.2021.
//

#include "Parser/SimpleTokenizers/OmitBlanksValidator.hpp"

namespace nastya::parser {

std::optional<Token> OmitBlanksValidator::validate(const std::string& value, ParsingContext& context) const
{
    while (context.start_position < value.size() and isblank(value[context.start_position]))
    {
        ++context.start_position;
    }
    if (context.start_position == value.size())
    {
        return Token{TokenType::Eof, {}};
    }
    return {};
}

std::unique_ptr<IValidator> OmitBlanksValidator::create()
{
    auto result = std::make_unique<OmitBlanksValidator>();
    return std::unique_ptr<IValidator>(result.release());
}

}
