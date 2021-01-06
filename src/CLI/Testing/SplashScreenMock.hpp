//
// Created by caedus on 05.01.2021.
//

#pragma once

#include <gmock/gmock.h>

#include "CLI/Interface/ISplashScreen.hpp"

namespace nastya::cli::splashscreen {

using namespace ::testing;

class SplashScreenMock : public ISplashScreen {
public:
    MOCK_METHOD(const std::vector<std::string>&, getMessage, (), (override));
};

}
