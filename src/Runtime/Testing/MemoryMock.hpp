//
// Created by caedus on 03.01.2021.
//

#pragma once

#include <gmock/gmock.h>

#include "Runtime/Interface/IMemory.hpp"

namespace nastya::runtime {

using namespace ::testing;

class MemoryMock : public IMemory {
public:
    MOCK_METHOD(bool, registerVariableOnHeap, (const typesystem::LabelObject& variableName,
                                               const typesystem::ObjectStorage& objectStorage), (override));
    MOCK_METHOD(const typesystem::ObjectStorage&, getFromHeap, (const typesystem::LabelObject& variableName), (const, override));
    MOCK_METHOD(bool, registerVariableOnStack, (const typesystem::LabelObject& variableName,
                                         const typesystem::ObjectStorage& objectStorage), (override));
    MOCK_METHOD(typesystem::ObjectStorage&, getFromStack, (const typesystem::LabelObject& variableName), (const, override));
    MOCK_METHOD(void, pushStackFrame, (), (override));
    MOCK_METHOD(bool, popStackFrame, (), (override));
};
}