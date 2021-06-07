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

struct MemoryTest : public ::testing::Test
{
    MemoryTest()
    {
        initModules(object_factory, module_registry);
    }

    nastya::parser::ObjectFactory object_factory;
    nastya::modules::ModuleRegistry module_registry;
    nastya::tokens::Tokenizer tokenizer;
};

TEST_F(MemoryTest, DefineSyntax)
{
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    tokenizer.reset("(Define DummyList '(1 2 3))");
    auto expression = expressionBuilder.build();
    machine.run(expression);

    std::vector test_cases = {std::make_pair("DummyList", "(1 2 3)"),
                              std::make_pair("(Head DummyList)", "1"),
                              std::make_pair("(Tail DummyList)", "(2 3)")};

    for (auto test_case : test_cases)
    {
        expressionBuilder.reset();
        tokenizer.reset(test_case.first);
        auto expression = expressionBuilder.build();
        auto result = machine.run(expression);
        EXPECT_EQ(result.toString(), test_case.second);
    }
}

TEST_F(MemoryTest, LetInSyntax)
{
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    tokenizer.reset("(Let (Pi 3.14) (Two 2) In (* Pi Two))");
    auto expression = expressionBuilder.build();
    auto result = machine.run(expression);

   EXPECT_EQ(result.toString(), "6.28");
}

TEST_F(MemoryTest, LetInSyntaxInLambda)
{
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    tokenizer.reset("(Define CircleLength (Lambda (radius) (Let (Pi 3.14) In (* 2 Pi radius))))");
    auto expression = expressionBuilder.build();
    machine.run(expression);

    expressionBuilder.reset();
    tokenizer.reset("(CircleLength 2)");
    expression = expressionBuilder.build();
    auto result = machine.run(expression);
    EXPECT_EQ(result.toString(), "12.56");
}

