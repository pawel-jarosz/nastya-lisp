//
// Created by caedus on 03.01.2021.
//

#include <gtest/gtest.h>

#include "Builtins/BuiltinsModuleBuilder.hpp"
#include "Modules/ModuleRegistry.hpp"

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
    EXPECT_EQ(registered_modules.size(), 2);
    EXPECT_EQ(registered_modules[0], "Lang.Compare");
    EXPECT_EQ(registered_modules[1], "Lang.Lists");
}

TEST_F(BuiltinsModuleBuilderTest, verifyListsModule) {
    EXPECT_TRUE(registry.isAvailableFunction("Head"));
    EXPECT_TRUE(registry.isAvailableFunction("Tail"));
    EXPECT_TRUE(registry.isAvailableFunction("Quote"));
    EXPECT_FALSE(registry.isAvailableFunction("Concat"));
    EXPECT_EQ(registry.getFunction("Head").getName(), "Head");
    EXPECT_EQ(registry.getFunction("Tail").getName(), "Tail");
    EXPECT_EQ(registry.getFunction("Quote").getName(), "Quote");
}

TEST_F(BuiltinsModuleBuilderTest, verifyCompareModule) {
    EXPECT_TRUE(registry.isAvailableFunction("Equal"));
    EXPECT_TRUE(registry.isAvailableFunction("Compare"));
    EXPECT_EQ(registry.getFunction("Equal").getName(), "Equal");
    EXPECT_EQ(registry.getFunction("Compare").getName(), "Compare");
}

}
