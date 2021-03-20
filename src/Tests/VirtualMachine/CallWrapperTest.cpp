//
// Created by caedus on 20.03.2021.
//

#include "VirtualMachine/CallWrapper.hpp"
#include "Runtime/GenericEvaluator.hpp"
#include "Runtime/Testing/MemoryMock.hpp"
#include "Runtime/Testing/MachineMock.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace nastya::vm {
using namespace ::testing;
using namespace runtime;

class DummyEvaluator : public runtime::GenericEvaluator {
public:
    DummyEvaluator() : GenericEvaluator("dummy") {}
    MOCK_METHOD(typesystem::ObjectStorage, preExecute, (const typesystem::ListObject& object,
                                                 IMachine& vm), (const, override));
    MOCK_METHOD(typesystem::ObjectStorage, evaluate, (IMemory& memory, const typesystem::ObjectStorage& object),
                (const, override));
    MOCK_METHOD(void, postExecute, (IMachine& vm), (const, override));
};

TEST(CallWrapperTest, testWithReference) {
    DummyEvaluator evaluator;
    EXPECT_CALL(evaluator, preExecute);
    EXPECT_CALL(evaluator, evaluate);
    EXPECT_CALL(evaluator, postExecute);
    MemoryMock memory;
    MachineMock machine;

    typesystem::ListObject testing_list;
    typesystem::ObjectStorage object;
    CallWrapper wrapper(evaluator);
    wrapper.preExecute(testing_list, machine);
    wrapper.evaluate(memory, object);
    wrapper.postExecute(machine);
}

TEST(CallWrapperTest, testWithPointer) {
    DummyEvaluator* evaluator = new DummyEvaluator;
    EXPECT_CALL(*evaluator, preExecute);
    EXPECT_CALL(*evaluator, evaluate);
    EXPECT_CALL(*evaluator, postExecute);
    MemoryMock memory;
    MachineMock machine;

    typesystem::ListObject testing_list;
    typesystem::ObjectStorage object;
    CallWrapper wrapper(evaluator);
    wrapper.preExecute(testing_list, machine);
    wrapper.evaluate(memory, object);
    wrapper.postExecute(machine);
}

}

