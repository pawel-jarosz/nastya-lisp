//
// Created by caedus on 06.01.2021.
//

#include <gtest/gtest.h>

#include "CLI/SplashScreen/SplashScreen.hpp"

namespace nastya::cli::splashscreen {

using namespace ::testing;

TEST(SplashScreenTest, testSplashScreen)
{
    std::vector<std::string> message = {"Line1", "Line2", "Line3"};

    SplashScreen screen(message);
    auto result = screen.getMessage();
    EXPECT_EQ(message.size(), result.size());
    for (size_t i = 0; i < message.size(); i++)
    {
        EXPECT_EQ(message[i], result[i]);
    }
}

}  // namespace nastya::cli::splashscreen
