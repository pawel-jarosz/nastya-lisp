//
// Created by caedus on 22.12.2020.
//

#pragma once
#include <gmock/gmock.h>

#include "Runtime/Interface/IMachine.hpp"

namespace nastya::runtime {
using namespace ::testing;
class MachineMock : public IMachine
{
public:
    MOCK_METHOD(typesystem::ObjectStorage, run, (const typesystem::ObjectStorage&), (override));
    MOCK_METHOD(bool, registerVariableOnHeap, (const typesystem::LabelObject& variableName,
        const typesystem::ObjectStorage& objectStorage), (override));
    MOCK_METHOD(const typesystem::ObjectStorage&, getFromHeap, (const typesystem::LabelObject& variableName), (const, override));
    MOCK_METHOD(bool, registerVariableOnStack, (const typesystem::LabelObject& variableName,
        const typesystem::ObjectStorage& objectStorage), (override));
    MOCK_METHOD(typesystem::ObjectStorage&, getFromStack, (const typesystem::LabelObject& variableName), (const, override));
    MOCK_METHOD(void, pushStackFrame, (), (override));
    MOCK_METHOD(bool, popStackFrame, (), (override));
};

}  // namespace nastya::vm