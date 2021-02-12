//
// Created by caedus on 03.12.2020.
//

#include <cctype>
#include <regex>

#include <Parser/ParserException.hpp>

#include "Parser/SimpleTokenizers/AtomValidator.hpp"
#include "Parser/SimpleTokenizers/OmitBlanksValidator.hpp"
#include "Parser/SimpleTokenizers/ReservedCharacterValidator.hpp"
#include "Parser/SimpleTokenizers/StringValidator.hpp"
#include "Parser/Tokenizer.hpp"

namespace nastya::parser {

namespace {

std::unique_ptr<IValidator> validator_builder() {
    auto composite = std::make_unique<CompositeValidator>();
    composite->addValidator(OmitBlanksValidator::create())
        .addValidator(ReservedCharacterValidator::create())
        .addValidator(StringValidator::create())
        .addValidator(AtomValidator::create());
    return std::unique_ptr<IValidator>(composite.release());
}

}  // namespace

Tokenizer::Tokenizer(std::string text) : m_text{std::move(text)}, m_context{0}
{
}

Token Tokenizer::getToken()
{
    const auto validator = validator_builder();
    auto result = validator->validate(m_text, m_context);
    if (not result) {
        BUT_THROW(ParserException, "Invalid token");
    }
    m_context.start_position = m_context.end_position;
    return *result;
}

bool Tokenizer::isEmpty()
{
    while (m_context.start_position < m_text.size() and isblank(m_text[m_context.start_position]))
    {
        ++m_context.start_position;
    }
    return (m_context.start_position == m_text.size());
}
void Tokenizer::reset(std::string code)
{
    m_text = std::move(code);
    m_context.start_position = 0;
}

}  // namespace nastya::parser
