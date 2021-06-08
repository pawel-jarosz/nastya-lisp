//
// Created by caedus on 07.06.2021.
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

struct SimpleCommandsTest : public ::testing::Test {
    SimpleCommandsTest() {
        initModules(object_factory, module_registry);
    }

    nastya::parser::ObjectFactory object_factory;
    nastya::modules::ModuleRegistry module_registry;
    nastya::tokens::Tokenizer tokenizer;
};


TEST_F(SimpleCommandsTest, ListsCommand) {
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    std::vector test_cases = {
        std::make_pair("(Head '(1 2 3))", "1"),
        std::make_pair("(Tail '(1 2 3))", "(2 3)"),
    std::make_pair("(Quote (1 2 3))", "(1 2 3)")
    };
    for (auto test_case: test_cases) {
        expressionBuilder.reset();
        tokenizer.reset(test_case.first);
        auto expression = expressionBuilder.build();
        auto result = machine.run(expression);
        EXPECT_EQ(result.toString(), test_case.second);
    }
}

TEST_F(SimpleCommandsTest, ComparisionCommands) {
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    std::vector test_cases = {
        std::make_pair("(Greater 1 2)", "#false"),
        std::make_pair("(Greater 2 2)", "#false"),
        std::make_pair("(Greater 3 2)", "#true"),
        std::make_pair("(GreaterOrEqual 1 2)", "#false"),
        std::make_pair("(GreaterOrEqual 2 2)", "#true"),
        std::make_pair("(GreaterOrEqual 3 2)", "#true"),
        std::make_pair("(LowerOrEqual 1 2)", "#true"),
        std::make_pair("(LowerOrEqual 2 2)", "#true"),
        std::make_pair("(LowerOrEqual 3 2)", "#false"),
        std::make_pair("(Lower 1 2)", "#true"),
        std::make_pair("(Lower 2 2)", "#false"),
        std::make_pair("(Lower 3 2)", "#false"),
        std::make_pair("(Compare 1 2)", "-1"),
        std::make_pair("(Compare 2 2)", "0"),
        std::make_pair("(Compare 3 2)", "1")
    };
    for (auto test_case: test_cases) {
        expressionBuilder.reset();
        tokenizer.reset(test_case.first);
        auto expression = expressionBuilder.build();
        auto result = machine.run(expression);
        EXPECT_EQ(result.toString(), test_case.second);
    }
}

TEST_F(SimpleCommandsTest, IfCommand) {
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    std::vector test_cases = {
        std::make_pair("(If (Greater 3 2) 1 2)", "1"),
        std::make_pair("(If (Greater 1 2) 1 2)", "2"),
        std::make_pair("(Cond ((Lower 1 2) 1) ((Greater 2 1) 2))", "1"),
        std::make_pair("(Cond ((Greater 1 2) 1) ((Greater 2 1) 2))", "2"),
        std::make_pair("(Cond ((Greater 1 2) 1) ((GreaterOrEqual 1 2) 2) ((Equal 1 2) 3) (Else 4))", "4")
    };
    for (auto test_case: test_cases) {
        expressionBuilder.reset();
        tokenizer.reset(test_case.first);
        auto expression = expressionBuilder.build();
        auto result = machine.run(expression);
        EXPECT_EQ(result.toString(), test_case.second);
    }
}
