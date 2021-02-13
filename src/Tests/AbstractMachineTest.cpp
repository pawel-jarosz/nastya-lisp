//
// Created by caedus on 05.01.2021.
//

#include <Runtime/GenericEvaluator.hpp>
#include <gtest/gtest.h>

#include "Builtins/BuiltinsException.hpp"
#include "LispExpression/Testing/ListBuilder.hpp"
#include "TypeSystem/Types/NumberObject.hpp"
#include "Modules/ModuleException.hpp"
#include "Modules/Testing/ModuleRegistryMock.hpp"
#include "VirtualMachine/Machine.hpp"
#include "VirtualMachine/MachineRuntimeException.hpp"

namespace nastya::vm {

using namespace ::testing;

class TestingModuleException : public modules::ModuleException {
public:
    TestingModuleException() : modules::ModuleException("filename", 123, "function", "message") {

    }
};

class TestingBuiltinsException : public builtins::BuiltinsException {
public:
    TestingBuiltinsException() : builtins::BuiltinsException("filename", 123, "function", "message") {

    }
};

struct TestingEvaluator : public runtime::GenericEvaluator {
    TestingEvaluator() : runtime::GenericEvaluator("Quote") {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& arg) const override {
        throw TestingBuiltinsException();
    }
};

TEST(AbstractMachineTest, testAtomValueCase) {
    auto number = std::make_unique<lisp::typesystem::NumberObject>(2);
    lisp::ObjectStorage argument_and_expected_result(std::move(number));
    modules::ModuleRegistryMock module_registry;
    Machine machine(module_registry);
    EXPECT_EQ(machine.run(argument_and_expected_result).toString(),
              argument_and_expected_result.toString());
}

TEST(AbstractMachineTest, testEmptyListCase) {
    lisp::testing::ListBuilder builder;
    auto argument_and_expected_result = builder.build();
    modules::ModuleRegistryMock module_registry;
    Machine machine(module_registry);
    EXPECT_EQ(machine.run(argument_and_expected_result).toString(),
              argument_and_expected_result.toString());

}

TEST(AbstractMachineTest, testWhenModuleThrowsException) {
    lisp::testing::ListBuilder builder;
    auto argument = builder.addLabel("Quote").build();
    modules::ModuleRegistryMock module_registry;
    TestingModuleException testing_exception;
    EXPECT_CALL(module_registry, getFunction(_)).WillOnce(Throw(testing_exception));
    Machine machine(module_registry);
    EXPECT_THROW(machine.run(argument), TestingModuleException);

}

TEST(AbstractMachineTest, testWhenFunctionThrowsException) {
    lisp::testing::ListBuilder builder;
    auto argument = builder.addLabel("Quote").build();
    modules::ModuleRegistryMock module_registry;
    TestingEvaluator evaluator;
    EXPECT_CALL(module_registry, getFunction(_)).WillOnce(ReturnRef(evaluator));
    Machine machine(module_registry);
    EXPECT_THROW(machine.run(argument), TestingBuiltinsException);
}

}
