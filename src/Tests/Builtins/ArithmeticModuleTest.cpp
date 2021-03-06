//
// Created by caedus on 20.03.2021.
//

#include <algorithm>

#include <Runtime/Testing/MemoryMock.hpp>
#include <gtest/gtest.h>

#include "Builtins/Arithmetic/ArithmeticEvaluators.hpp"
#include "Builtins/BuiltinsException.hpp"
#include "TypeSystem/Types/ListObject.hpp"
#include "Utilities/LispCast.hpp"
#include "Utilities/ListBuilder.hpp"

#define ASSERT_THROW(condition, msg) \
    if (condition) \
    { \
        BUT_THROW(BuiltinsException, msg); \
    }

namespace nastya::builtins::arithmetic {

using namespace ::testing;
using namespace utils;

TEST(ArithmeticEvaluatorTest, testAdditionName)
{
    AddEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "+");
}

TEST(ArithmeticEvaluatorTest, additionOfIntegerList)
{
    AddEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1).addNumber(2).addNumber(3).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "6");
}

TEST(ArithmeticEvaluatorTest, additionOfFloatingList)
{
    AddEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1.2f).addNumber(2.3f).addNumber(3.4f).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "6.9");
}

TEST(ArithmeticEvaluatorTest, additionOfMixedList1)
{
    AddEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1).addNumber(2.3f).addNumber(3).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "6.3");
}

TEST(ArithmeticEvaluatorTest, additionOfMixedList2)
{
    AddEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(2.3f).addNumber(1).addNumber(3.4f).addNumber(5).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "11.7");
}

TEST(ArithmeticEvaluatorTest, testSubtractionName)
{
    SubtractionEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "-");
}

TEST(ArithmeticEvaluatorTest, subtractionOfIntegerList)
{
    SubtractionEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1).addNumber(2).addNumber(3).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "-4");
}

TEST(ArithmeticEvaluatorTest, subtractionOfFloatingList)
{
    SubtractionEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1.4f).addNumber(0.2f).addNumber(0.3f).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "0.9");
}

TEST(ArithmeticEvaluatorTest, subtractionOfMixedList1)
{
    SubtractionEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1.4f).addNumber(2).addNumber(0.3f).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "-0.9");
}

TEST(ArithmeticEvaluatorTest, subtractionOfMixedList2)
{
    SubtractionEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1).addNumber(2.3f).addNumber(3).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "-4.3");
}

TEST(ArithmeticEvaluatorTest, testMultiplyName)
{
    MultiplyEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "*");
}

TEST(ArithmeticEvaluatorTest, productOfIntegerList)
{
    MultiplyEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(2).addNumber(3).addNumber(4).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "24");
}

TEST(ArithmeticEvaluatorTest, productOfFloatingList)
{
    MultiplyEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(2.4f).addNumber(0.1f).addNumber(2.5f).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "0.6");
}

TEST(ArithmeticEvaluatorTest, productOfMixedList1)
{
    MultiplyEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1.4f).addNumber(2).addNumber(0.3f).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "0.84");
}

TEST(ArithmeticEvaluatorTest, productOfMixedList2)
{
    MultiplyEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1).addNumber(2.3f).addNumber(3).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "6.9");
}

TEST(ArithmeticEvaluatorTest, testDivisionName)
{
    DivisionEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "/");
}

TEST(ArithmeticEvaluatorTest, divisionProductOfIntegerList)
{
    DivisionEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(24).addNumber(6).addNumber(2).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "2");
}

TEST(ArithmeticEvaluatorTest, divisionProductOfFloatingList)
{
    DivisionEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(2.4f).addNumber(0.1f).addNumber(2.5f).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "9.6");
}

TEST(ArithmeticEvaluatorTest, divisionProductOfMixedList1)
{
    DivisionEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1.4f).addNumber(2).addNumber(0.1f).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "7");
}

TEST(ArithmeticEvaluatorTest, divisionProductOfMixedList2)
{
    DivisionEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.addNumber(1).addNumber(0.1f).addNumber(2).build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "5");
}

}
