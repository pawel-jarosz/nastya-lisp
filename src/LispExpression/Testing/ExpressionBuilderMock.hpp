//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "LispExpression/Interface/IExpressionBuilder.hpp"

namespace nastya::lisp::testing {

class ExpressionBuilderMock : public IExpressionBuilder {
public:
    MOCK_METHOD(ObjectStorage, build, (), (override));
    MOCK_METHOD(void, reset, (), (override));
};

}