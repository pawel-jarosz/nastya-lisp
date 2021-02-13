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

Tokenizer::Tokenizer() : Tokenizer("")
{

}


Tokenizer::Tokenizer(std::string text) : m_text{std::move(text)}, m_context{0}
{
    addValidator(OmitBlanksValidator::create())
    .addValidator(ReservedCharacterValidator::create())
    .addValidator(StringValidator::create())
    .addValidator(AtomValidator::create());
}

Token Tokenizer::getToken()
{
    auto result = validate(m_text, m_context);
    if (not result) {
        BUT_THROW(ParserException, "Invalid token");
    }
    m_context.start_position = m_context.end_position;
    return *result;
}

void Tokenizer::reset(std::string code)
{
    m_text = std::move(code);
    m_context.start_position = 0;
}

}  // namespace nastya::parser
