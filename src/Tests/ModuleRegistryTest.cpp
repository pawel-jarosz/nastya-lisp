//
// Created by caedus on 21.12.2020.
//

#include <gtest/gtest.h>

#include "Modules/ModuleRegistry.hpp"
#include "Modules/Testing/ModuleMock.hpp"
#include "Modules/ModuleException.hpp"
#include "Modules/Module.hpp"
#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::modules::testing {

class DummyModule : public Module {
public:
    DummyModule() : Module("DummyModule") {

    }
};

struct IdEvaluator : nastya::runtime::IEvaluator {
    std::string getName() const override {
        return "Id";
    }

    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& arguments) const override {
        return arguments;
    }
};

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
    EXPECT_THROW(registry.registerModule(module), ModuleException);
    registry.registerModule(module2);
    auto list = registry.getAvailableModules();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], module_name1);
    EXPECT_EQ(list[1], module_name2);
}

TEST(ModuleRegistryTest, testFindingFunctions) {
    DummyModule module;
    IdEvaluator evaluator;
    module.registerFunction(evaluator);
    ModuleRegistry registry;
    EXPECT_THROW(registry.getFunction("DummyFUnction"), ModuleException);
    registry.registerModule(module);
    EXPECT_NO_THROW(registry.getFunction("Id"));
}

}  // namespace nastya::modules::testing