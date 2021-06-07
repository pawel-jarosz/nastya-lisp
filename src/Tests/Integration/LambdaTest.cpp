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

struct LambdaTest : public ::testing::Test
{
    LambdaTest()
    {
        initModules(object_factory, module_registry);
    }

    nastya::parser::ObjectFactory object_factory;
    nastya::modules::ModuleRegistry module_registry;
    nastya::tokens::Tokenizer tokenizer;
};

TEST_F(LambdaTest, IsEmpty)
{
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    tokenizer.reset("(Define IsEmpty (Lambda (list) (If (Equal list '()) #true #false)))");
    auto expression = expressionBuilder.build();
    machine.run(expression);

    std::vector test_cases = {std::make_pair("(IsEmpty '(1 2 3))", "#false"),
                              std::make_pair("(IsEmpty '())", "#true")};

    for (auto test_case : test_cases)
    {
        expressionBuilder.reset();
        tokenizer.reset(test_case.first);
        auto expression = expressionBuilder.build();
        auto result = machine.run(expression);
        EXPECT_EQ(result.toString(), test_case.second);
    }
}

TEST_F(LambdaTest, GetLength)
{
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    tokenizer.reset("(Define IsEmpty (Lambda (list) (If (Equal list '()) #true #false)))");
    auto expression = expressionBuilder.build();
    machine.run(expression);
    expressionBuilder.reset();
    tokenizer.reset("(Define GetSize (Lambda (list) (If (IsEmpty list) 0 (+ 1 (GetSize (Tail list))))))");
    expression = expressionBuilder.build();
    machine.run(expression);

    std::vector test_cases = {std::make_pair("(GetSize '(1 2 3))", "3"),
                              std::make_pair("(GetSize '())", "0")};
    
    for (auto test_case : test_cases)
    {
        expressionBuilder.reset();
        tokenizer.reset(test_case.first);
        auto expression = expressionBuilder.build();
        auto result = machine.run(expression);
        EXPECT_EQ(result.toString(), test_case.second);
    }
}