//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "Parser/Interface/IParser.hpp"

namespace nastya::lisp::testing {

class ExpressionBuilderMock : public IParser
{
public:
    MOCK_METHOD(typesystem::ObjectStorage, build, (), (override));
    MOCK_METHOD(void, reset, (), (override));
};

}