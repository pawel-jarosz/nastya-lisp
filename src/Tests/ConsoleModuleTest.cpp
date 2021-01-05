//
// Created by caedus on 05.01.2021.
//

#include <gtest/gtest.h>

#include "CLI/Module/ConsoleEvaluators.hpp"
#include "CLI/Testing/ConsoleManagerMock.hpp"
#include "CLI/Module/ConsoleModule.hpp"
#include "CLI/Module/ConsoleModuleBuilder.hpp"
#include "Modules/ModuleRegistry.hpp"
#include "Runtime/Testing/MemoryMock.hpp"
#include "LispExpression/Testing/ListBuilder.hpp"

namespace nastya::cli {

TEST(ConsoleModuleTest, testShutdown) {
    ConsoleManagerMock console_manager;
    runtime::MemoryMock memory;
    lisp::testing::ListBuilder builder;
    auto argument = builder.build();
    EXPECT_CALL(console_manager, shutdown());
    module::ShutdownEvaluator evaluator(console_manager);
    EXPECT_EQ(evaluator.getName(), "Exit-Console");
    EXPECT_THROW(evaluator.evaluate(memory, argument), std::runtime_error);
}

TEST(ConsoleModuleTest, testModule) {
    ConsoleManagerMock console_manager;
    auto& module = module::ConsoleModule::getInstance(console_manager);
    EXPECT_EQ(module.getModuleName(), "CLI.App");
    EXPECT_TRUE(module.isFunctionAvailable("Exit-Console"));
    EXPECT_NO_THROW(module.getFunction("Exit-Console"));
}

TEST(ConsoleModuleTest, testModuleRegistration) {
    ConsoleManagerMock console_manager;
    modules::ModuleRegistry registry;
    module::ConsoleModuleBuilder builder(registry, console_manager);
    builder.build();
    EXPECT_EQ(registry.getAvailableModules()[0], "CLI.App");
}

}
