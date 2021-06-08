//
// Created by caedus on 08.06.2021.
//

#include <gtest/gtest.h>

#include "Builtins/BuiltinsBuilder.hpp"
#include "Builtins/BuiltinsModulesFactory.hpp"
#include "Modules/ModuleRegistry.hpp"
#include "Parser/ObjectFactory.hpp"
#include "Parser/ObjectFactoryBuilder.hpp"
#include "Parser/Parser.hpp"
#include "Tokenizer/Tokenizer.hpp"
#include "VirtualMachine/Machine.hpp"

static void initModules(nastya::parser::ObjectFactory& object_factory, nastya::modules::ModuleRegistry& module_registry)
{
    nastya::parser::ObjectFactoryBuilder object_factory_builder(object_factory);
    object_factory_builder.build();
    nastya::builtins::BuiltinsModulesFactory modules_factory;
    nastya::builtins::BuiltinsBuilder builtins_builder(module_registry, modules_factory);
    builtins_builder.build();
}

struct ComplexCommandsTest : public ::testing::Test {
    ComplexCommandsTest() {
        initModules(object_factory, module_registry);
    }

    nastya::parser::ObjectFactory object_factory;
    nastya::modules::ModuleRegistry module_registry;
    nastya::tokens::Tokenizer tokenizer;
};


TEST_F(ComplexCommandsTest, Fibonacci) {
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    std::vector test_cases = {
        std::make_pair("(Define Fibonacci (Lambda (x) (If (LowerOrEqual x 1) 1 (+ (Fibonacci (- x 1)) (Fibonacci (- x 2))))))", "Fibonacci"),
        std::make_pair("(Fibonacci 0)", "1"),
        std::make_pair("(Fibonacci 1)", "1"),
        std::make_pair("(Fibonacci 2)", "2"),
        std::make_pair("(Fibonacci 3)", "3"),
        std::make_pair("(Fibonacci 4)", "5"),
        std::make_pair("(Fibonacci 5)", "8"),
        std::make_pair("(Fibonacci 6)", "13")
    };
    for (auto test_case: test_cases) {
        expressionBuilder.reset();
        tokenizer.reset(test_case.first);
        auto expression = expressionBuilder.build();
        auto result = machine.run(expression);
        EXPECT_EQ(result.toString(), test_case.second);
    }
}

TEST_F(ComplexCommandsTest, CondFibonacci) {
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    std::vector test_cases = {
        std::make_pair("(Define Fibonacci (Lambda (x) (Cond ((Equal x 0) 0) ((Equal x 1) 1) (Else (+ (Fibonacci (- x 1)) (Fibonacci (- x 2)))))))", "Fibonacci"),
        std::make_pair("(Fibonacci 0)", "0"),
        std::make_pair("(Fibonacci 1)", "1"),
        std::make_pair("(Fibonacci 2)", "1"),
        std::make_pair("(Fibonacci 3)", "2"),
        std::make_pair("(Fibonacci 4)", "3"),
        std::make_pair("(Fibonacci 5)", "5"),
        std::make_pair("(Fibonacci 6)", "8"),
        std::make_pair("(Fibonacci 7)", "13")
    };
    for (auto test_case: test_cases) {
        expressionBuilder.reset();
        tokenizer.reset(test_case.first);
        auto expression = expressionBuilder.build();
        auto result = machine.run(expression);
        EXPECT_EQ(result.toString(), test_case.second);
    }
}

TEST_F(ComplexCommandsTest, Factorial) {
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    std::vector test_cases = {
        std::make_pair("(Define Factorial (Lambda (x) (If (Equal x 0) 1 (* x (Factorial (- x 1))))))", "Factorial"),
        std::make_pair("(Factorial 0)", "1"),
        std::make_pair("(Factorial 1)", "1"),
        std::make_pair("(Factorial 2)", "2"),
        std::make_pair("(Factorial 3)", "6"),
        std::make_pair("(Factorial 4)", "24")
    };
    for (auto test_case: test_cases) {
        expressionBuilder.reset();
        tokenizer.reset(test_case.first);
        auto expression = expressionBuilder.build();
        auto result = machine.run(expression);
        EXPECT_EQ(result.toString(), test_case.second);
    }
}