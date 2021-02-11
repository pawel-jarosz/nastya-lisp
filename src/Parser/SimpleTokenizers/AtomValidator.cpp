//
// Created by caedus on 11.02.2021.
//

#include "Parser/SimpleTokenizers/AtomValidator.hpp"

#include "Parser/SimpleTokenizers/BooleanValidator.hpp"
#include "Parser/SimpleTokenizers/LabelValidator.hpp"
#include "Parser/SimpleTokenizers/NumberValidator.hpp"

namespace nastya::parser {

std::optional<Token> AtomValidator::validate(const std::string& value, ParsingContext& context) const
{
    context.end_position = context.start_position;
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

std::unique_ptr<IValidator> AtomValidator::create()
{
    auto result = std::make_unique<AtomValidator>();
    result->addValidator(BooleanValidator::create())
        .addValidator(NumberValidator::create())
        .addValidator(LabelValidator::create());
    return std::unique_ptr<IValidator>(result.release());
}
}

