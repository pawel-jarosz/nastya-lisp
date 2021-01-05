//
// Created by caedus on 05.01.2021.
//

#pragma once

#include <gmock/gmock.h>

#include "CLI/Interface/IConsoleManager.hpp"

namespace nastya::cli {

using namespace ::testing;

class ConsoleManagerMock : public interface::IConsoleManager {
public:
    MOCK_METHOD(void, shutdown, (), (override));
    MOCK_METHOD(int, run, (), (override));
};

}
