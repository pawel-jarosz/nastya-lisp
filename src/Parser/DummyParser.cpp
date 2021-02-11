//
// Created by caedus on 03.12.2020.
//

#include <cctype>
#include <regex>

#include <Parser/ParserException.hpp>
#include "Parser/DummyParser.hpp"
#include "Parser/SimpleTokenizers/AtomValidator.hpp"
#include "Parser/SimpleTokenizers/StringValidator.hpp"


namespace nastya::parser {

namespace {

std::unique_ptr<IValidator> validator_builder() {
    auto composite = std::make_unique<CompositeValidator>();
    composite->addValidator(StringValidator::create())
        .addValidator(AtomValidator::create());
    return std::unique_ptr<IValidator>(composite.release());
}

// <0> - parsed string
// <1> - position of next token
std::optional<std::pair<Token, size_t>> parse(const std::string& text, size_t pos)
{
    ParsingContext context {pos};
    const auto validator = validator_builder();
    auto result = validator->validate(text, context);
    if (not result) {
        BUT_THROW(ParserException, "Invalid token");
    }
    return {std::pair(*result, context.end_position)};
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
