//
// Created by caedus on 22.12.2020.
//

#include <gtest/gtest.h>
#include "Parser/DummyParser.hpp"
#include "LispExpression/LispExpressionBuilder.hpp"
#include "LispExpression/ObjectFactoryBuilder.hpp"
#include "LispExpression/ObjectFactory.hpp"
#include "VirtualMachine/Machine.hpp"
#include "Modules/ModuleRegistry.hpp"
#include "Builtins/BuiltinsModuleBuilder.hpp"

TEST(VMTest, testHeadList) {
    const std::string test_instruction = "(Head (Quote (2 3 4)))";
    nastya::parser::DummyParser parser(test_instruction);
    nastya::lisp::ObjectFactory object_factory;
    nastya::lisp::ObjectFactoryBuilder object_factory_builder(object_factory);
    object_factory_builder.build();
    nastya::lisp::LispExpressionBuilder expression_builder(parser, object_factory);
    auto expression = expression_builder.build();
    nastya::modules::ModuleRegistry module_registry;
    nastya::builtins::BuiltinsModuleBuilder builtins_builder(module_registry);
    builtins_builder.build();
    nastya::vm::Machine machine(module_registry);
    auto result = machine.run(expression);
    EXPECT_EQ(result.toString(), "2");
}
