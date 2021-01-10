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
    EXPECT_EQ(registered_modules.size(), 3);
    EXPECT_EQ(registered_modules[0], "Lang.Compare");
    EXPECT_EQ(registered_modules[1], "Lang.Lists");
    EXPECT_EQ(registered_modules[2], "Lang.Syntax");
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
}
