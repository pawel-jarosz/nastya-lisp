//
// Created by caedus on 09.01.2021.
//
#include <gtest/gtest.h>

#include "Builtins/BuiltinsException.hpp"
#include "Builtins/Compare/CompareEvaluators.hpp"
#include "Builtins/Compare/CompareModule.hpp"
#include "Modules/ModuleException.hpp"
#include "Parser/Testing/ListBuilder.hpp"
#include "Runtime/Testing/MemoryMock.hpp"
#include "TypeSystem/Types/NumberObject.hpp"

namespace nastya::builtins::compare {
using namespace ::testing;

TEST(CompareEvaluatorTest, testCompareName)
{
    CompareEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "Compare");
}

TEST(CompareEvaluatorTest, testCompareSuccessStory)
{
    CompareEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    lisp::testing::ListBuilder builder;
    auto argument_list = builder.addNumber(2).addNumber(3).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "-1");
}

TEST(CompareEvaluatorTest, testCompareFails)
{
    CompareEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // Evaluator receives as an argument not a list
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto not_enough_arguments = builder.addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, not_enough_arguments), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto too_many_arguments = builder.addNumber(2).addNumber(3).addNumber(4).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, too_many_arguments), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto one_non_comparable = builder.addLabel("dummy").addNumber(3).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, one_non_comparable), BuiltinsException);
    }
}

TEST(CompareEvaluatorTest, testEqualName)
{
    EqualEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "Equal");
}

TEST(CompareEvaluatorTest, testEqualSuccessStory)
{
    EqualEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    lisp::testing::ListBuilder builder;
    auto argument_list = builder.addNumber(2).addNumber(2).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "#true");
}

TEST(CompareEvaluatorTest, testEqualFails)
{
    EqualEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // Evaluator receives as an argument not a list
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto not_enough_arguments = builder.addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, not_enough_arguments), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto too_many_arguments = builder.addNumber(2).addNumber(3).addNumber(4).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, too_many_arguments), BuiltinsException);
    }
}

TEST(CompareEvaluatorTest, testLowerSuccessStory)
{
    {
        LowerEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(3).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#true");
    }
    {
        LowerEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(2).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#false");
    }
    {
        LowerEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(4).addNumber(3).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#false");
    }
}

TEST(CompareEvaluatorTest, testLowerFails)
{
    LowerEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // Evaluator receives as an argument not a list
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto not_enough_arguments = builder.addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, not_enough_arguments), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto too_many_arguments = builder.addNumber(2).addNumber(3).addNumber(4).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, too_many_arguments), BuiltinsException);
    }
}

TEST(CompareEvaluatorTest, testLowerOrEqualSuccessStory)
{
    {
        LowerOrEqualEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(3).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#true");
    }
    {
        LowerOrEqualEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(2).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#true");
    }
    {
        LowerOrEqualEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(4).addNumber(3).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#false");
    }
}

TEST(CompareEvaluatorTest, testLowerOrEqualFails)
{
    LowerOrEqualEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // Evaluator receives as an argument not a list
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto not_enough_arguments = builder.addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, not_enough_arguments), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto too_many_arguments = builder.addNumber(2).addNumber(3).addNumber(4).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, too_many_arguments), BuiltinsException);
    }
}

TEST(CompareEvaluatorTest, testGreaterOrEqualSuccessStory)
{
    {
        GreaterOrEqualEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(3).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#false");
    }
    {
        GreaterOrEqualEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(2).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#true");
    }
    {
        GreaterOrEqualEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(4).addNumber(3).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#true");
    }
}

TEST(CompareEvaluatorTest, testGreaterOrEqualFails)
{
    GreaterOrEqualEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // Evaluator receives as an argument not a list
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto not_enough_arguments = builder.addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, not_enough_arguments), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto too_many_arguments = builder.addNumber(2).addNumber(3).addNumber(4).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, too_many_arguments), BuiltinsException);
    }
}

TEST(CompareEvaluatorTest, testGreaterSuccessStory)
{
    {
        GreaterEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(3).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#false");
    }
    {
        GreaterEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(2).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#false");
    }
    {
        GreaterEvaluator evaluator;
        runtime::MemoryMock memory_mock;
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(4).addNumber(3).build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "#true");
    }
}

TEST(CompareEvaluatorTest, testGreaterFails)
{
    GreaterEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // Evaluator receives as an argument not a list
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto not_enough_arguments = builder.addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, not_enough_arguments), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto too_many_arguments = builder.addNumber(2).addNumber(3).addNumber(4).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, too_many_arguments), BuiltinsException);
    }
}

}  // namespace nastya::builtins::compare
