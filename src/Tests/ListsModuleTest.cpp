//
// Created by caedus on 03.01.2021.
//

#include <gtest/gtest.h>

#include "Builtins/BuiltinsException.hpp"
#include "Builtins/Lists/ListsEvaluators.hpp"
#include "Builtins/Lists/ListsModule.hpp"
#include "Parser/Testing/ListBuilder.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "Modules/ModuleException.hpp"
#include "Runtime/Testing/MemoryMock.hpp"
#include "Utilities/LispCastException.hpp"

namespace nastya::builtins::lists {

using namespace ::testing;
using namespace utils;

TEST(ListsEvaluatorTest, testHeadName) {
    HeadEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "Head");
}

TEST(ListsEvaluatorTest, testHeadSuccessStory) {
    HeadEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    lisp::testing::ListBuilder builder;
    auto argument_list = builder.openList().addNumber(2).addNumber(1).closeList().build();
    auto result = evaluator.evaluate(memory_mock, argument_list);
    EXPECT_EQ(result.toString(), "2");
}

TEST(ListsEvaluatorTest, testHeadFailure) {
    HeadEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.openList().addNumber(2)
            .addNumber(1).closeList().build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "2");
    }
    {
        // Evaluator receives as an argument not a list
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(
            new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), LispCastException);
    }
    {
        // Evaluator receives empty argument list
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.openList().closeList().build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), LispCastException);
    }
    {
        // Evaluator receives more than one elements on list
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        // Empty list as an argument
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.openList().closeList().build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
}

TEST(ListsEvaluatorTest, testTail) {
    TailEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "Tail");
}

TEST(ListsEvaluatorTest, testTailSuccessStory)
{
    TailEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // ((1 2 3))
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.openList().addNumber(1).addNumber(2).addNumber(3).closeList().build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "(2 3)");
    }
    {
        // ((1))
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.openList().addNumber(1).closeList().build();
        auto result = evaluator.evaluate(memory_mock, argument_list);
        EXPECT_EQ(result.toString(), "()");
    }
}

TEST(ListsEvaluatorTest, testTailFailure)
{
    TailEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // 2
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(
            new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), LispCastException);
    }
    {
        // (())
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.openList().closeList().build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        // (2 2)
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        // (2)
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), LispCastException);
    }
}

TEST(ListsEvaluatorTest, testQuote) {
    QuoteEvaluator evaluator;
    EXPECT_EQ(evaluator.getName(), "Quote");
}

TEST(ListsEvaluatorTest, testQuoteSuccessStory) {
    QuoteEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // (2)
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).build();
        EXPECT_EQ(evaluator.evaluate(memory_mock, argument_list).toString(), "2");
    }
    {
        // (())
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.openList().closeList().build();
        EXPECT_EQ(evaluator.evaluate(memory_mock, argument_list).toString(), "()");
    }
}

TEST(ListsEvaluatorTest, testQuoteFailure) {
    QuoteEvaluator evaluator;
    runtime::MemoryMock memory_mock;
    {
        // 2
        typesystem::ObjectStorage argument_list(std::unique_ptr<typesystem::IObject>(
            new typesystem::NumberObject(2)));
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), LispCastException);
    }
    {
        // (2 2)
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.addNumber(2).addNumber(2).build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
    {
        // ()
        lisp::testing::ListBuilder builder;
        auto argument_list = builder.build();
        EXPECT_THROW(evaluator.evaluate(memory_mock, argument_list), BuiltinsException);
    }
}

TEST(ListsModuleTest, testModule) {
    const auto module = lists::create_module_builder()->build();
    EXPECT_EQ(module->getModuleName(), "Lang.Lists");
    EXPECT_FALSE(module->isFunctionAvailable("Concat"));

    auto registered_functions = module->getFunctionsList();
    std::vector<std::string> functions = {"Head", "Tail", "Quote"};

    EXPECT_EQ(registered_functions.size(), functions.size());
    EXPECT_THROW(module->getFunction("Concat"), modules::ModuleException);
    for (const auto& function_name: functions) {
        EXPECT_TRUE(module->isFunctionAvailable(function_name));
        auto it = std::find(registered_functions.begin(), registered_functions.end(), function_name);
        EXPECT_NE(it, registered_functions.end());
        auto& evaluator = module->getFunction(function_name);
        EXPECT_EQ(evaluator.getName(), function_name);
    }
}

}
