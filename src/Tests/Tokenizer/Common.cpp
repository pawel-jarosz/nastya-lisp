#include "Common.hpp"

namespace nastya::tokens {

Token create_boolean_token(bool value)
{
    return Token{TokenType::Boolean, value};
}

Token create_integer_token(int value)
{
    return Token{TokenType::Integer, value};
}

Token create_floating_token(float value)
{
    return Token{TokenType::Floating, value};
}

Token create_label_token(std::string value)
{
    return Token{TokenType::Label, value};
}

Token create_string_token(std::string value)
{
    std::stringstream ss;
    for (const auto& ch : value)
    {
        if (ch == '\"')
        {
            ss << "\\\"";
            continue;
        }
        ss << ch;
    }
    return Token{TokenType::String, ss.str()};
}


}