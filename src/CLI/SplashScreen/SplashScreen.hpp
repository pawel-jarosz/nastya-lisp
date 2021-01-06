//
// Created by caedus on 06.01.2021.
//

#include "CLI/Interface/ISplashScreen.hpp"

namespace nastya::cli::splashscreen {

class SplashScreen : public ISplashScreen {
public:
    explicit SplashScreen(std::vector<std::string> message);
    const std::vector<std::string>& getMessage() override;
private:
    std::vector<std::string> m_message;
};

}