//
// Created by caedus on 03.12.2020.
//

#pragma once

#include <gmock/gmock.h>

#include "Parser/Interface/IParser.hpp"

namespace nastya::parser {

class ParserMock : public IParser
{
public:
    MOCK_METHOD(Token, getToken, (), (override));
    MOCK_METHOD(void, reset, (std::string code), (override));
};

}  // namespace nastya::parser
