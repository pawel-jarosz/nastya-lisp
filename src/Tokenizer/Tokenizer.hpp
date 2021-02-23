//
// Created by caedus on 03.12.2020.
//

#pragma once

#include <string>

#include "Tokenizer/Interface/ITokenizer.hpp"
#include "Tokenizer/TokenProviders/TokenProvidersAggregator.hpp"
#include "Tokenizer/Types/ParsingContext.hpp"

namespace nastya::tokens {

class Tokenizer : public ITokenizer
, private TokenProvidersAggregator
{
public:
    Tokenizer();
    explicit Tokenizer(std::string text);
    Token getToken() override;
    void reset(std::string code) override;

private:
    std::string m_text;
    ParsingContext m_context;

};

}  // namespace nastya::tokens
