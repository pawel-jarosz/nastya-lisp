//
// Created by caedus on 03.12.2020.
//

#include <cctype>
#include <regex>
#include <sstream>

#include <Parser/ParserException.hpp>

#include "Parser/DummyParser.hpp"

namespace nastya::parser {

namespace {

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

// <0> - parsed string
// <1> - position of next token
std::pair<Token, size_t> read_string(const std::string& text, size_t start_pos)
{
    bool escaped = false;
    ++start_pos;
    std::stringstream stream;

    while (start_pos < text.size())
    {
        if (text[start_pos] == '\\')
        {
            escaped = true;
            continue;
        }

        bool is_quotation = (text[start_pos] == '\"');
        if (is_quotation and escaped)
        {
            escaped = false;
            stream << "\"";
            continue;
        }
        else if (is_quotation)
        {
            const auto next_pos = analyse_quotation(text, start_pos + 1);
            return std::make_pair(Token{TokenType::String, {stream.str()}}, next_pos);
        }
        stream << text[start_pos];
        ++start_pos;
    }
    BUT_THROW(ParserException, "Not terminated quotation mark");
}

Token value_to_token(const std::string& value)
{
    if (value == "#true" or value == "#false")
    {
        bool boolean_value = value.compare("#true") == 0;
        return Token{TokenType::Boolean, boolean_value};
    }
    std::regex integer_number_regex("(-)?[0-9]+");
    std::smatch m;
    if (std::regex_match(value, m, integer_number_regex))
    {
        return Token{TokenType::Integer, std::stoi(value)};
    }
    std::regex float_number_regex("(-)?[0-9]+\\.[0-9]+(e(-)?[0-9]+)?(f|d)?");
    if (std::regex_match(value, m, float_number_regex))
    {
        return Token{TokenType::Floating, std::stof(value)};
    }
    std::regex label_regex("[A-Za-z][A-Za-z0-9_-]*[A_Za-z0-9_]?");
    if (not std::regex_match(value, m, label_regex))
    {
        std::stringstream ss;
        ss << "Value " << value << "is not valid label!";
        BUT_THROW(ParserException, ss.str());
    }
    return Token{TokenType::Label, value};
}

// <0> - parsed string
// <1> - position of next token
std::pair<Token, size_t> read_value(const std::string& text, size_t start_pos)
{
    std::stringstream ss;
    while (start_pos < text.size() and not isblank(text[start_pos]) and text[start_pos] != ')')
    {
        ss << text[start_pos++];
    }
    return std::make_pair(value_to_token(ss.str()), start_pos);
}

// <0> - parsed string
// <1> - position of next token
std::optional<std::pair<Token, size_t>> parse(const std::string& text, size_t pos)
{
    if (text[pos] == '\"')
    {
        return read_string(text, pos);
    }
    if (isprint(text[pos]))
    {
        return read_value(text, pos);
    }
    return {};
}
}  // namespace

DummyParser::DummyParser(std::string text) : m_text{std::move(text)}, m_pos{0}
{
}

Token DummyParser::getToken()
{
    while (m_pos < m_text.size() and isblank(m_text[m_pos]))
    {
        ++m_pos;
    }
    if (m_pos == m_text.size())
    {
        return Token{TokenType::Eof, {}};
    }

    switch (m_text[m_pos++])
    {
        case '(':
            return Token{TokenType::S_expr_begin, {}};
        case ')':
            return Token{TokenType::S_expr_end, {}};
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '%':
            if (m_pos < m_text.size() and isblank(m_text[m_pos])) {
                return Token{TokenType::Label, std::string{m_text[m_pos - 1]}};
            }
            break;
        case '\'':
            return Token{TokenType::Quote, {}};
    }
    auto parsing_result = parse(m_text, m_pos - 1);
    if (parsing_result.has_value())
    {
        m_pos = parsing_result->second;
        return parsing_result->first;
    }
    return Token{TokenType::Eof, {}};
}

bool DummyParser::isEmpty()
{
    while (m_pos < m_text.size() and isblank(m_text[m_pos]))
    {
        ++m_pos;
    }
    return (m_pos == m_text.size());
}
void DummyParser::reset(std::string code)
{
    m_text = std::move(code);
    m_pos = 0;
}

}  // namespace nastya::parser
