//
// Created by caedus on 05.01.2021.
//

#include <gtest/gtest.h>

#include "CLI/Module/ConsoleEvaluators.hpp"
#include "CLI/Module/ConsoleModule.hpp"
#include "CLI/Module/ConsoleModuleRegistration.hpp"
#include "CLI/Testing/ConsoleManagerMock.hpp"
#include "Parser/Testing/ListBuilder.hpp"
#include "Modules/ModuleRegistry.hpp"
#include "Runtime/Testing/MemoryMock.hpp"

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
    auto module = nastya::cli::module::create_module(console_manager);
    EXPECT_EQ(module->getModuleName(), "CLI.App");
    EXPECT_TRUE(module->isFunctionAvailable("Exit-Console"));
    EXPECT_NO_THROW(module->getFunction("Exit-Console"));
}

TEST(ConsoleModuleTest, testModuleRegistration) {
    ConsoleManagerMock console_manager;
    modules::ModuleRegistry registry;
    module::ConsoleModuleRegistration builder(registry, console_manager);
    builder.build();
    EXPECT_EQ(registry.getAvailableModules()[0], "CLI.App");
}

}
