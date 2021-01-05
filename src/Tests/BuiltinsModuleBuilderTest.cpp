//
// Created by caedus on 03.01.2021.
//

#include <gtest/gtest.h>

#include "Builtins/BuiltinsModuleBuilder.hpp"
#include "Modules/ModuleRegistry.hpp"

namespace nastya::builtins {
using namespace testing;

TEST(BuiltinsModuleBuilderTest, verifyBuilder) {
    modules::ModuleRegistry registry;
    BuiltinsModuleBuilder builder(registry);
    builder.build();
    auto registered_modules = registry.getAvailableModules();
    EXPECT_EQ(registered_modules.size(), 1);
    EXPECT_EQ(registered_modules[0], "Lang.Lists");
    EXPECT_TRUE(registry.isAvailableFunction("Head"));
    EXPECT_TRUE(registry.isAvailableFunction("Tail"));
    EXPECT_TRUE(registry.isAvailableFunction("Quote"));
    EXPECT_FALSE(registry.isAvailableFunction("Concat"));
    EXPECT_EQ(registry.getFunction("Head").getName(), "Head");
    EXPECT_EQ(registry.getFunction("Tail").getName(), "Tail");
    EXPECT_EQ(registry.getFunction("Quote").getName(), "Quote");
}

}
