//
// Created by caedus on 07.06.2021.
//

#include <gtest/gtest.h>

#include "Builtins/BuiltinsBuilder.hpp"
#include "Builtins/BuiltinsModulesFactory.hpp"
#include "CLI/ConsoleManager.hpp"
#include "CLI/IO/StreamWrapperFactory.hpp"
#include "CLI/PreloadFromFile.hpp"
#include "CLI/SplashScreen/SplashScreen.hpp"
#include "Modules/ModuleRegistry.hpp"
#include "Parser/ObjectFactory.hpp"
#include "Parser/ObjectFactoryBuilder.hpp"
#include "Parser/Parser.hpp"
#include "Tokenizer/Tokenizer.hpp"
#include "VirtualMachine/Machine.hpp"

void initModules(nastya::parser::ObjectFactory& object_factory, nastya::modules::ModuleRegistry& module_registry)
{
    nastya::parser::ObjectFactoryBuilder object_factory_builder(object_factory);
    object_factory_builder.build();
    nastya::builtins::BuiltinsModulesFactory modules_factory;
    nastya::builtins::BuiltinsBuilder builtins_builder(module_registry, modules_factory);
    builtins_builder.build();
}

TEST(SimpleCommandsTest, ListsCommand) {
    nastya::parser::ObjectFactory object_factory;
    nastya::modules::ModuleRegistry module_registry;
    initModules(object_factory, module_registry);
    nastya::tokens::Tokenizer tokenizer;
    nastya::parser::Parser expressionBuilder(tokenizer, object_factory);
    nastya::vm::Machine machine(module_registry);

    tokenizer.reset("(Head '(1 2 3))");
    auto expression = expressionBuilder.build();
    auto result = machine.run(expression);
    EXPECT_EQ(result.toString(), "1");
}