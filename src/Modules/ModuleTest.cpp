//
// Created by caedus on 22.12.2020.
//

#include <gtest/gtest.h>

#include "Modules/Module.hpp"

namespace nastya::modules {
using namespace ::testing;

const std::string module_name = "TestingModule";

struct DummyEvaluator : public runtime::IEvaluator
{
    DummyEvaluator(std::string name) : evaluator_name{name}, called(false)
    {
    }

    std::string getName() const override
    {
        return evaluator_name;
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

struct DummyMemory : runtime::IMemory
{
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
    testing_module.registerFunction(evaluator1);
    EXPECT_TRUE(testing_module.isFunctionAvailable("Head"));
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
}

TEST_F(ModuleTest, testFunctionCall)
{
    DummyMemory memory;
    lisp::ObjectStorage storage;
    testing_module.registerFunction(evaluator1);
    auto& function = testing_module.getFunction("Head");
    function.evaluate(memory, storage);
    EXPECT_TRUE(evaluator1.called);
}

}  // namespace nastya::modules
