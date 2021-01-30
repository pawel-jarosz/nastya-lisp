//
// Created by caedus on 22.12.2020.
//

#include <Runtime/GenericEvaluator.hpp>
#include <gtest/gtest.h>

#include "Modules/Module.hpp"
#include "Modules/ModuleException.hpp"
#include "Runtime/Testing/MemoryMock.hpp"

namespace nastya::modules {
using namespace ::testing;

const std::string module_name = "TestingModule";

struct DummyEvaluator : public runtime::GenericEvaluator
{
    DummyEvaluator(std::string name) : GenericEvaluator{name}, called(false)
    {
    }
    lisp::ObjectStorage evaluate(runtime::IMemory&, const lisp::ObjectStorage& obj) const override
    {
        lisp::ObjectStorage res;
        called = true;
        return res;
    }
    std::string evaluator_name;
    mutable bool called;
};

struct ModuleTest : public Test
{
    ModuleTest() : testing_module{module_name}, evaluator1("Head"), evaluator2("Tail")
    {
    }

    Module testing_module;
    DummyEvaluator evaluator1, evaluator2;
};

TEST_F(ModuleTest, testModuleName)
{
    EXPECT_EQ(testing_module.getModuleName(), module_name);
}

TEST_F(ModuleTest, testFunctionRegistration)
{
    EXPECT_FALSE(testing_module.isFunctionAvailable("Head"));
    testing_module.registerFunction(evaluator1);
    EXPECT_TRUE(testing_module.isFunctionAvailable("Head"));
    EXPECT_THROW(testing_module.registerFunction(evaluator1), ModuleException);
}

TEST_F(ModuleTest, testFunctionList)
{
    testing_module.registerFunction(evaluator1);
    testing_module.registerFunction(evaluator2);
    auto list = testing_module.getFunctionsList();
    EXPECT_TRUE(testing_module.isFunctionAvailable("Head"));
    EXPECT_TRUE(testing_module.isFunctionAvailable("Tail"));
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list[0], std::string("Head"));
    EXPECT_EQ(list[1], std::string("Tail"));
    EXPECT_THROW(testing_module.getFunction("dummy"), ModuleException);
}

TEST_F(ModuleTest, testFunctionCall)
{
    runtime::MemoryMock memory;
    lisp::ObjectStorage storage;
    testing_module.registerFunction(evaluator1);
    auto& function = testing_module.getFunction("Head");
    function.evaluate(memory, storage);
    EXPECT_TRUE(evaluator1.called);
}

}  // namespace nastya::modules
