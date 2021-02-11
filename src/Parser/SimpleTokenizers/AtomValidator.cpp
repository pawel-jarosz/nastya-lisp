//
// Created by caedus on 11.02.2021.
//

#include "Parser/SimpleTokenizers/AtomValidator.hpp"

namespace nastya::parser {

std::optional<Token> AtomValidator::validate(const std::string& value, ParsingContext& context) const
{
    if (not isprint(value[context.end_position]))
    {
        return {};
    }
    std::stringstream ss;
    while (context.end_position < value.size() and not isblank(value[context.end_position]) and value[context.end_position] != ')')
    {
        ss << value[context.end_position++];
    }
    const auto token = ss.str();
    return CompositeValidator::validate(token, context);

}

}

