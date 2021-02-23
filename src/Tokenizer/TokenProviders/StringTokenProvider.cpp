//
// Created by caedus on 11.02.2021.
//

#include "Tokenizer/TokenProviders/StringTokenProvider.hpp"
#include "Tokenizer/TokenizerException.hpp"

namespace nastya::tokens {

StringTokenProvider::StringTokenProvider()
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
        BUT_THROW(TokenizerException, "Invalid syntax - quotation is not closed before the end");
    }
    while (next_pos < text.size() and isblank(text[next_pos]))
    {
        ++next_pos;
    }
    return next_pos;
}

std::optional<Token> StringTokenProvider::getTokenIfAvailable(const std::string& value, ParsingContext& context) const
{
    if (value[context.start_position] != '\"')
    {
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
    BUT_THROW(TokenizerException, "Not terminated quotation mark");
}
std::unique_ptr<ITokenProvider> StringTokenProvider::create()
{
    auto result = std::make_unique<StringTokenProvider>();
    return std::unique_ptr<ITokenProvider>(result.release());
}

}  // namespace nastya::tokens
