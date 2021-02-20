//
// Created by caedus on 20.02.2021.
//

#include <Runtime/GenericEvaluator.hpp>
#include <gtest/gtest.h>

#include "Modules/Module.hpp"
#include "Modules/ModuleException.hpp"
#include "Modules/ModuleRegistry.hpp"
#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::modules::testing {

class DummyModule : public Module {
public:
    DummyModule() : Module("DummyModule") {

    }
};

struct IdEvaluator : nastya::runtime::GenericEvaluator {
    IdEvaluator() : nastya::runtime::GenericEvaluator("Id") {}
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& arguments) const override {
        return arguments;
    }
};

using namespace ::testing;

TEST(ModuleRegistryTest, testRegister)
{
    const std::string module1_name{"DummyModule1"};
    const std::string module2_name{"DummyModule2"};
    auto module1 = std::make_unique<Module>(module1_name);
    auto copy_of_module1 = std::make_unique<Module>(module1_name);
    auto module2 = std::make_unique<Module>(module2_name);
    ModuleRegistry registry;
    registry.registerModule(std::unique_ptr<IModule>(module1.release()));
    EXPECT_THROW(registry.registerModule(std::unique_ptr<IModule>(copy_of_module1.release())), ModuleException);
    registry.registerModule(std::unique_ptr<IModule>(module2.release()));
    auto list = registry.getAvailableModules();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], module1_name);
    EXPECT_EQ(list[1], module2_name);
}

TEST(ModuleRegistryTest, testFindingFunctions) {
    auto module = std::make_unique<DummyModule>();
    std::unique_ptr<runtime::IEvaluator> evaluator(new IdEvaluator());
    module->registerFunction(std::move(evaluator));
    ModuleRegistry registry;
    EXPECT_THROW(registry.getFunction("DummyFUnction"), ModuleException);
    registry.registerModule(std::unique_ptr<IModule>(module.release()));
    EXPECT_NO_THROW(registry.getFunction("Id"));
    EXPECT_TRUE(registry.isAvailableFunction("Id"));
    EXPECT_FALSE(registry.isAvailableFunction("NotExist"));
}

}  // namespace nastya::modules::testing