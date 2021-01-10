//
// Created by caedus on 09.01.2021.
//

#include <gtest/gtest.h>

#include "Builtins/BuiltinsException.hpp"
#include "Builtins/Syntax/SyntaxEvaluators.hpp"
#include "Builtins/Syntax/SyntaxModule.hpp"
#include "LispExpression/Testing/ListBuilder.hpp"
#include "LispExpression/TypeSystem/NumberObject.hpp"
#include "Modules/ModuleException.hpp"
#include "Runtime/Testing/MemoryMock.hpp"

namespace nastya::builtins::syntax {
using namespace ::testing;

TEST(SyntaxEvaluatorTest, testIfName) {
    IfEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "If");
}

TEST(SyntaxEvaluatorTest, testIfSuccess) {
    IfEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addBoolean(true).addNumber(1).addNumber(2).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "1");
    }
    {
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addBoolean(false).addNumber(1).addNumber(2).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "2");
    }
}

TEST(SyntaxEvaluatorTest, testIfFails) {
    IfEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        lisp::ObjectStorage argument_is_not_a_list(std::unique_ptr<lisp::IObject>(
            new lisp::typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_is_not_a_list), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto not_enough_arguments = builder.addBoolean(true).addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, not_enough_arguments), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto too_many_arguments = builder.addBoolean(true)
                                      .addNumber(1)
                                      .addNumber(2)
                                      .addNumber(3).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, too_many_arguments), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto first_is_not_boolean = builder.addNumber(1)
            .addNumber(2)
            .addNumber(3).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, first_is_not_boolean), BuiltinsException);
    }
}

}
