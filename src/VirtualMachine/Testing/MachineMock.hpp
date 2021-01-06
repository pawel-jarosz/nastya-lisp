//
// Created by caedus on 22.12.2020.
//

#pragma once
#include <gmock/gmock.h>

#include "VirtualMachine/Interface/IMachine.hpp"

namespace nastya::vm {
using namespace ::testing;
class MachineMock : public IMachine
{
public:
    MOCK_METHOD(lisp::ObjectStorage, run, (const lisp::ObjectStorage&), (override));
};

}  // namespace nastya::vm