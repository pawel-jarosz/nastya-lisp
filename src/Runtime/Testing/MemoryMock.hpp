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
    MOCK_METHOD(bool, registerVariableOnHeap, (const lisp::typesystem::LabelObject& variableName,
                                               const lisp::ObjectStorage& objectStorage), (override));
    MOCK_METHOD(const lisp::ObjectStorage&, getFromHeap, (const lisp::typesystem::LabelObject& variableName), (const, override));
};
}