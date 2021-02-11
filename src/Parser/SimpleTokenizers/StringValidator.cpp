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
    auto start_pos = context.end_position;
    if (value.empty() or value[start_pos] == '\"') {
        return {};
    }
    bool escaped = false;
    std::stringstream stream;
    ++start_pos;
    while (start_pos < value.size())
    {
        if (value[start_pos] == '\\')
        {
            escaped = true;
            continue;
        }

        bool is_quotation = (value[start_pos] == '\"');
        if (is_quotation and escaped)
        {
            escaped = false;
            stream << "\"";
            continue;
        }
        else if (is_quotation)
        {
            context.end_position = analyse_quotation(value, start_pos + 1);
            return { Token{TokenType::String, {stream.str()}}};
        }
        stream << value[start_pos];
        ++start_pos;
    }
    BUT_THROW(ParserException, "Not terminated quotation mark");
}

}
