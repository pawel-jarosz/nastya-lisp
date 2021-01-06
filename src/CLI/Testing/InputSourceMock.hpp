//
// Created by caedus on 05.01.2021.
//

#pragma once

#include <gmock/gmock.h>

#include "CLI/Interface/IInputSource.hpp"

namespace nastya::cli::io {

using namespace ::testing;

class InputSourceMock : public IInputSource {
public:
    ~InputSourceMock() = default;
    MOCK_METHOD(std::string, readLine, (), (override));
};

}
