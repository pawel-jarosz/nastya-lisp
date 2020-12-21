//
// Created by caedus on 21.12.2020.
//

#include "Modules/Testing/ModuleMock.hpp"
#include "Modules/ModuleRegistry.hpp"

#include <gtest/gtest.h>

namespace nastya::modules::testing {

using namespace ::testing;

TEST(ModuleRegistryTest, testSingleModuleRegister) {
    ModuleMock module;
    const std::string module_name = "MockModule";
    EXPECT_CALL(module, getModuleName).WillRepeatedly(Return(module_name));
    ModuleRegistry registry;
    registry.registerModule(module);
}

}