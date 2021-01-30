//
// Created by caedus on 03.01.2021.
//

#include <gtest/gtest.h>

#include "Builtins/BuiltinsModuleBuilder.hpp"
#include "Modules/ModuleRegistry.hpp"

#include <iostream>

namespace nastya::builtins {
using namespace ::testing;

struct BuiltinsModuleBuilderTest : public Test {
    BuiltinsModuleBuilderTest() : registry(), builder(registry) {
        builder.build();
    }

    modules::ModuleRegistry registry;
    BuiltinsModuleBuilder builder;
};

TEST_F(BuiltinsModuleBuilderTest, basicExpectation) {
    auto registered_modules = registry.getAvailableModules();
    EXPECT_EQ(registered_modules.size(), 4);
    std::vector modules_list = {
        "Lang.Arithmetic",
        "Lang.Compare",
        "Lang.Lists",
        "Lang.Syntax"
    };
    for (const auto& module: modules_list) {
        const auto begin = registered_modules.cbegin();
        const auto end = registered_modules.cend();
        EXPECT_NE(std::find(begin, end, module), end);
    }
}

TEST_F(BuiltinsModuleBuilderTest, verifyListsModule) {
    std::vector<std::string> methods = {
        "Head",
        "Tail",
        "Quote"
    };
    for (const auto& method: methods) {
        EXPECT_TRUE(registry.isAvailableFunction(method));
        EXPECT_EQ(registry.getFunction(method).getName(), method);
    }
}

TEST_F(BuiltinsModuleBuilderTest, verifyCompareModule) {
    std::vector<std::string> methods = {
        "Compare",
        "Lower",
        "LowerOrEqual",
        "Equal",
        "GreaterOrEqual",
        "Greater"
    };
    for (const auto& method: methods) {
        EXPECT_TRUE(registry.isAvailableFunction(method));
        EXPECT_EQ(registry.getFunction(method).getName(), method);
    }
}

TEST_F(BuiltinsModuleBuilderTest, verifySyntaxModule) {
    std::vector<std::string> methods = {
        "If",
        "Cond"
    };
    for (const auto& method: methods) {
        EXPECT_TRUE(registry.isAvailableFunction(method));
        EXPECT_EQ(registry.getFunction(method).getName(), method);
    }
}

TEST_F(BuiltinsModuleBuilderTest, verifyArithmeticModule) {
    std::vector<std::string> methods = {
        "+"
    };
    for (const auto& method: methods) {
        EXPECT_TRUE(registry.isAvailableFunction(method));
        EXPECT_EQ(registry.getFunction(method).getName(), method);
    }
}
}
