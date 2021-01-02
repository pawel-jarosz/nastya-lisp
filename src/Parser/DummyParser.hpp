//
// Created by caedus on 03.12.2020.
//

#pragma once

#include "Parser/Interface/IParser.hpp"

#include <string>

namespace nastya::parser {

class DummyParser : public IParser {
public:
    DummyParser() = default;
    explicit DummyParser(std::string text);
    Token getToken() override;
    bool isEmpty() override;
    void reset(std::string code) override;
private:
    std::string m_text;
    size_t m_pos;
};

} // namespace nastya::parser
