#include "Tokenizer/Types/Token.hpp"

namespace nastya::tokens {

const std::map<TokenType, std::string> Converter::conversion_map = {{TokenType::Boolean, "Boolean"},
                                                                    {TokenType::Integer, "Integer"},
                                                                    {TokenType::Floating, "Floating"},
                                                                    {TokenType::String, "String"},
                                                                    {TokenType::Label, "Label"},
                                                                    {TokenType::S_expr_begin, "S_expr_begin"},
                                                                    {TokenType::S_expr_end, "S_expr_end"},
                                                                    {TokenType::Quote, "Quote"},
                                                                    {TokenType::Eof, "Eof"}};

namespace {

struct TokenPrinter
{
    explicit TokenPrinter(const Token& token, std::ostream& out) : m_token{token}, m_out{out}
    {
    }

    template <typename T>
    void operator()(T value)
    {
        m_out << " => " << value;
    }

    void operator()(bool value) {
        if (value) {
            m_out << " => " << "True";
        }
        else {
            m_out << " => " << "False";
        }
    }

    bool is_printable();

    const Token& m_token;
    std::ostream& m_out;
};

bool TokenPrinter::is_printable()
{
    switch (m_token.type)
    {
        case TokenType::Floating:
        case TokenType::Integer:
        case TokenType::String:
        case TokenType::Boolean:
        case TokenType::Label:
            return true;
        default:
            return false;
    }
}

}  // namespace

std::ostream& operator<<(std::ostream& out, const TokenType& type)
{
    out << Converter::conversion_map.at(type);
    return out;
}

std::ostream& operator<<(std::ostream& out, const Token& token)
{
    out << "Token " << token.type;

    TokenPrinter print(token, out);
    if (print.is_printable())
    {
        std::visit(print, token.value);
    }
    return out;
}

bool operator==(const Token& lhs, const Token& rhs)
{
    if (lhs.type != rhs.type)
    {
        return false;
    }
    return (lhs.value == rhs.value);
}

}  // namespace nastya::tokens