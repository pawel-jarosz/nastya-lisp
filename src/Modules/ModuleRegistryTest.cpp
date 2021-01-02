//
// Created by caedus on 21.12.2020.
//

#include <gtest/gtest.h>

#include "Modules/ModuleRegistry.hpp"
#include "Modules/Testing/ModuleMock.hpp"

namespace nastya::modules::testing {

using namespace ::testing;

TEST(ModuleRegistryTest, testRegister)
{
    ModuleMock module, module2;
    const std::string module_name1 = "MockModule";
    const std::string module_name2 = "MockModule2";
    EXPECT_CALL(module, getModuleName).WillRepeatedly(Return(module_name1));
    EXPECT_CALL(module2, getModuleName).WillRepeatedly(Return(module_name2));
    ModuleRegistry registry;
    registry.registerModule(module);
    registry.registerModule(module2);
    auto list = registry.getAvailableModules();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], module_name1);
    EXPECT_EQ(list[1], module_name2);
}

// TODO: Add testcase with two modules with the same name and finding function in multiple modules

}  // namespace nastya::modules::testing