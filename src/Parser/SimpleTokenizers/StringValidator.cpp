//
// Created by caedus on 11.02.2021.
//

#include "Parser/SimpleTokenizers/StringValidator.hpp"
#include "Parser/ParserException.hpp"

namespace nastya::parser {

StringValidator::StringValidator()
{
}

size_t analyse_quotation(const std::string& text, size_t next_pos)
{
    if (next_pos == text.size() or text[next_pos] == ')')
    {
        return next_pos;
    }
    if (next_pos < text.size() and not isblank(text[next_pos]))
    {
        BUT_THROW(ParserException, "Invalid syntax - quotation is not closed before the end");
    }
    while (next_pos < text.size() and isblank(text[next_pos]))
    {
        ++next_pos;
    }
    return next_pos;
}

std::optional<Token> StringValidator::validate(const std::string& value, ParsingContext& context) const
{
    if (value[context.start_position] != '\"') {
        return {};
    }
    context.end_position = context.start_position;
    bool escaped = false;
    ++context.end_position;
    std::stringstream stream;

    while (context.end_position < value.size())
    {
        if (value[context.end_position] == '\\')
        {
            escaped = true;
            continue;
        }

        bool is_quotation = (value[context.end_position] == '\"');
        if (is_quotation and escaped)
        {
            escaped = false;
            stream << "\"";
            continue;
        }
        else if (is_quotation)
        {
            context.end_position = analyse_quotation(value, context.end_position + 1);
            return {Token{TokenType::String, {stream.str()}}};
        }
        stream << value[context.end_position];
        ++context.end_position;
    }
    BUT_THROW(ParserException, "Not terminated quotation mark");
}
std::unique_ptr<IValidator> StringValidator::create()
{
    auto result = std::make_unique<StringValidator>();
    return std::unique_ptr<IValidator>(result.release());
}

}
