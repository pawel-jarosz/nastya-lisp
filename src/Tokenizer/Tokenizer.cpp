//
// Created by caedus on 03.12.2020.
//

#include <cctype>
#include <regex>

#include "Tokenizer/TokenizerException.hpp"

#include "Tokenizer/TokenProviders/AtomicValueTokenProvider.hpp"
#include "Tokenizer/TokenProviders/OmitBlanks.hpp"
#include "Tokenizer/TokenProviders/ReservedCharacterTokenProvider.hpp"
#include "Tokenizer/TokenProviders/StringTokenProvider.hpp"
#include "Tokenizer/Tokenizer.hpp"

namespace nastya::parser {

Tokenizer::Tokenizer() : Tokenizer("")
{

}


Tokenizer::Tokenizer(std::string text) : m_text{std::move(text)}, m_context{0}
{
    addValidator(OmitBlanks::create())
    .addValidator(ReservedCharacterTokenProvider::create())
    .addValidator(StringTokenProvider::create())
    .addValidator(AtomicValueTokenProvider::create());
}

Token Tokenizer::getToken()
{
    auto result = getTokenIfAvailable(m_text, m_context);
    if (not result) {
        BUT_THROW(TokenizerException, "Invalid token");
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
