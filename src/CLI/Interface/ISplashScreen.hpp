//
// Created by caedus on 06.01.2021.
//

#pragma once

#include <vector>
#include <string>

namespace nastya::cli::splashscreen {

class ISplashScreen {
public:
    virtual ~ISplashScreen() = default;
    virtual const std::vector<std::string>& getMessage() = 0;
};

}
