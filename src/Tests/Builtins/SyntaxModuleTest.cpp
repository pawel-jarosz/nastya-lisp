//
// Created by caedus on 09.01.2021.
//

#include <gtest/gtest.h>

#include "Builtins/BuiltinsException.hpp"
#include "Builtins/Syntax/SyntaxEvaluators.hpp"
#include "Builtins/Syntax/SyntaxModule.hpp"
#include "Modules/ModuleException.hpp"
#include "Utilities/ListBuilder.hpp"
#include "Runtime/Testing/MemoryMock.hpp"
#include "TypeSystem/Types/NumberObject.hpp"

namespace nastya::builtins::syntax {
using namespace ::testing;
using namespace utils;

TEST(SyntaxEvaluatorTest, testIfName)
{
    IfEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "If");
}

TEST(SyntaxEvaluatorTest, testIfSuccess)
{
    IfEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        ListBuilder builder;
        auto argument_list = builder.addBoolean(true).addNumber(1).addNumber(2).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "1");
    }
    {
        ListBuilder builder;
        auto argument_list = builder.addBoolean(false).addNumber(1).addNumber(2).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "2");
    }
}

TEST(SyntaxEvaluatorTest, testIfFails)
{
    IfEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        typesystem::ObjectStorage argument_is_not_a_list(
            std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_is_not_a_list), BuiltinsException);
    }
    {
        ListBuilder builder;
        auto not_enough_arguments = builder.addBoolean(true).addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, not_enough_arguments), BuiltinsException);
    }
    {
        ListBuilder builder;
        auto too_many_arguments = builder.addBoolean(true).addNumber(1).addNumber(2).addNumber(3).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, too_many_arguments), BuiltinsException);
    }
    {
        ListBuilder builder;
        auto first_is_not_boolean = builder.addNumber(1).addNumber(2).addNumber(3).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, first_is_not_boolean), BuiltinsException);
    }
}

TEST(SyntaxEvaluatorTest, testCondName)
{
    CondEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "Cond");
}

TEST(SyntaxEvaluatorTest, testCondSuccess)
{
    CondEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // With else on begin
        ListBuilder builder;
        auto argument_list = builder.openList().addLabel("Else").addNumber(2).closeList().build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "2");
    }
    {
        // Omit false condition and return true
        ListBuilder builder;
        auto argument_list = builder.openList()
                                 .addBoolean(false)
                                 .addNumber(2)
                                 .closeList()
                                 .openList()
                                 .addBoolean(true)
                                 .addNumber(3)
                                 .closeList()
                                 .build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "3");
    }
    {
        // Omit false conditions and use else
        ListBuilder builder;
        auto argument_list = builder.openList()
                                 .addBoolean(false)
                                 .addNumber(2)
                                 .closeList()
                                 .openList()
                                 .addBoolean(false)
                                 .addNumber(3)
                                 .closeList()
                                 .openList()
                                 .addLabel("Else")
                                 .addNumber(4)
                                 .closeList()
                                 .build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "4");
    }
}

}  // namespace nastya::builtins::syntax
