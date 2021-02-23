//
// Created by caedus on 06.01.2021.
//

#include "CLI/SplashScreen/SplashScreen.hpp"

namespace nastya::cli::splashscreen {

SplashScreen::SplashScreen(std::vector<std::string> message) : m_message{std::move(message)}
{
}

const std::vector<std::string>& SplashScreen::getMessage()
{
    return m_message;
}

}  // namespace nastya::cli::splashscreen
