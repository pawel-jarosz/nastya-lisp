//
// Created by caedus on 20.02.2021.
//

#include "Modules/ModuleBuilder.hpp"
#include "Runtime/GenericEvaluatorFactory.hpp"

#include <gtest/gtest.h>

namespace nastya::modules::testing {

using namespace ::testing;

struct Evaluator : public runtime::IEvaluator {
    std::string getName() const override { return "DUMMY"; };
    typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                         runtime::IMachine& vm) const override { return typesystem::ObjectStorage(); };
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override {return typesystem::ObjectStorage();}
    void postExecute(runtime::IMachine& vm) const override {}
};

struct Evaluator2 : public runtime::IEvaluator {
    std::string getName() const override { return "DUMMY2"; };
    typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                         runtime::IMachine& vm) const override { return typesystem::ObjectStorage(); };
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override {return typesystem::ObjectStorage();}
    void postExecute(runtime::IMachine& vm) const override {}
};


bool evaluator_factory1_should_be_called = false;

struct EvaluatorFactory1 : public runtime::IEvaluatorFactory {
    std::unique_ptr<runtime::IEvaluator> create() const override {
        std::unique_ptr<runtime::IEvaluator> evaluator{new Evaluator};
        evaluator_factory1_should_be_called = true;
        return evaluator;
    }
};

bool evaluator_factory2_should_be_called = false;

struct EvaluatorFactory2 : public runtime::IEvaluatorFactory {
    std::unique_ptr<runtime::IEvaluator> create() const override {
        std::unique_ptr<runtime::IEvaluator> evaluator{new Evaluator2};
        evaluator_factory2_should_be_called = true;
        return evaluator;
    }
};

TEST(ModuleBuilderTest, onlyOneEvaluatorFactory) {
    using SingleModuleBuilder = ModuleBuilder<EvaluatorFactory1>;
    SingleModuleBuilder builder("TestModule");
    const auto& factories = builder.getFactories();
    EXPECT_EQ(factories.size(), 1);
    auto build_result = builder.build();
    EXPECT_TRUE(evaluator_factory1_should_be_called);
    evaluator_factory1_should_be_called = false;
}

TEST(ModuleBuilderTest, twoEvaluatorFactories) {
    using ModuleBuilder = ModuleBuilder<EvaluatorFactory1, EvaluatorFactory2>;
    ModuleBuilder builder("TestModule");
    const auto& factories = builder.getFactories();
    EXPECT_EQ(factories.size(), 2);
    auto build_result = builder.build();
    EXPECT_TRUE(evaluator_factory1_should_be_called);
    EXPECT_TRUE(evaluator_factory2_should_be_called);
}

}