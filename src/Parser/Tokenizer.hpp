//
// Created by caedus on 03.12.2020.
//

#pragma once

#include <string>

#include "Parser/Interface/IParser.hpp"
#include "Parser/SimpleTokenizers/CompositeValidator.hpp"
#include "Parser/Types/ParsingContext.hpp"

namespace nastya::parser {

class Tokenizer : public IParser, private CompositeValidator
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

}  // namespace nastya::parser
