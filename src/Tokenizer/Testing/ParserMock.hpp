//
// Created by caedus on 03.12.2020.
//

#pragma once

#include <gmock/gmock.h>

#include "Tokenizer/Interface/ITokenizer.hpp"

namespace nastya::tokens {

class ParserMock : public ITokenizer
{
public:
    MOCK_METHOD(Token, getToken, (), (override));
    MOCK_METHOD(void, reset, (std::string code), (override));
};

}  // namespace nastya::tokens
