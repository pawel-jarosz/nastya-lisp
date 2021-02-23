//
// Created by caedus on 03.01.2021.
//

#include <gtest/gtest.h>

#include "Builtins/BuiltinsException.hpp"
#include "Builtins/Lists/ListsEvaluators.hpp"
#include "Builtins/Lists/ListsModule.hpp"
#include "Modules/ModuleException.hpp"
#include "Utilities/ListBuilder.hpp"
#include "Runtime/Testing/MemoryMock.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "Utilities/LispCastException.hpp"
#include "Utilities/LispCast.hpp"
#include "Runtime/Testing/MachineMock.hpp"

namespace nastya::builtins::lists {

using namespace ::testing;
using namespace utils;

TEST(ListsEvaluatorTest, testHeadName)
{
    HeadEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "Head");
}

TEST(ListsEvaluatorTest, testHeadExecuteSuccessStory)
{
    HeadEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    ListBuilder builder;
    auto argument_list = builder.openList().addNumber(2).addNumber(1).closeList().build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "2");
}

TEST(ListsEvaluatorTest, testHeadExecuteFailure)
{
    HeadEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        ListBuilder builder;
        auto argument_list = builder.openList().addNumber(2).addNumber(1).closeList().build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "2");
    }
    {
        // Evaluator receives as an argument not a list
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), LispCastException);
    }
    {
        // Evaluator receives empty argument list
        ListBuilder builder;
        auto argument_list = builder.openList().closeList().build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        ListBuilder builder;
        auto argument_list = builder.addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), LispCastException);
    }
    {
        // Evaluator receives more than one elements on list
        ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        // Empty list as an argument
        ListBuilder builder;
        auto argument_list = builder.openList().closeList().build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
}

TEST(ListsEvaluatorTest, testTail)
{
    TailEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "Tail");
}

TEST(ListsEvaluatorTest, testTailExecuteSuccessStory)
{
    TailEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // ((1 2 3))
        ListBuilder builder;
        auto argument_list = builder.openList().addNumber(1).addNumber(2).addNumber(3).closeList().build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "(2 3)");
    }
    {
        // ((1))
        ListBuilder builder;
        auto argument_list = builder.openList().addNumber(1).closeList().build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "()");
    }
}

TEST(ListsEvaluatorTest, testTailExecuteFailure)
{
    TailEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // 2
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), LispCastException);
    }
    {
        // (())
        ListBuilder builder;
        auto argument_list = builder.openList().closeList().build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        // (2 2)
        ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        // (2)
        ListBuilder builder;
        auto argument_list = builder.addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), LispCastException);
    }
}

TEST(ListsEvaluatorTest, testQuote)
{
    QuoteEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "Quote");
}

TEST(ListsEvaluatorTest, testQuoteExecuteSuccessStory)
{
    QuoteEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // (2)
        ListBuilder builder;
        auto argument_list = builder.addNumber(2).build();
        EXPECT_EQ(evaluator.evaluate(memory_mock, argument_list).toString(), "2");
    }
    {
        // (())
        ListBuilder builder;
        auto argument_list = builder.openList().closeList().build();
        EXPECT_EQ(evaluator.evaluate(memory_mock, argument_list).toString(), "()");
    }
}

TEST(ListsEvaluatorTest, testQuoteExecuteFailure)
{
    QuoteEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // 2
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), LispCastException);
    }
    {
        // (2 2)
        ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        // ()
        ListBuilder builder;
        auto argument_list = builder.build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
}

TEST(ListsEvaluatorTest, testQuotePreExecute) {
    ListBuilder builder;
    QuoteEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    runtime::MachineMock machine_mock;
    auto command = builder.addLabel("Quote").openList().addNumber(1).addNumber(2).closeList().build();
    auto result = evaluator.preExecute(Cast::as_list(command), machine_mock);
    EXPECT_EQ(result.toString(), "((1 2))");
}

TEST(ListsModuleTest, testModuleFunctions)
{
    const auto module = lists::create_module_builder()->build();
    EXPECT_EQ(module->getModuleName(), "Lang.Lists");
    EXPECT_FALSE(module->isFunctionAvailable("Concat"));

    auto registered_functions = module->getFunctionsList();
    std::vector<std::string> functions = {"Head", "Tail", "Quote"};

    EXPECT_EQ(registered_functions.size(), functions.size());
    EXPECT_THROW(module->getFunction("Concat"), modules::ModuleException);
    for (const auto& function_name : functions)
    {
        EXPECT_TRUE(module->isFunctionAvailable(function_name));
        auto it = std::find(registered_functions.begin(), registered_functions.end(), function_name);
        EXPECT_NE(it, registered_functions.end());
        auto& evaluator = module->getFunction(function_name);
        EXPECT_EQ(evaluator.getName(), function_name);
    }
}

}  // namespace nastya::builtins::lists
