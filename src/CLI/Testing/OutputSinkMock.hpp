//
// Created by caedus on 05.01.2021.
//

#pragma once

#include <gmock/gmock.h>

#include "CLI/Interface/IOutputSink.hpp"

namespace nastya::cli::io {

using namespace ::testing;

class OutputSinkMock : public IOutputSink {
public:
    ~OutputSinkMock() override = default;
    MOCK_METHOD(void, writeLine, (std::string), (override));
    MOCK_METHOD(void, write, (std::string), (override));
};

}
