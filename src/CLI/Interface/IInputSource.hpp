//
// Created by caedus on 06.01.2021.
//

#pragma once

#include <string>

namespace nastya::cli::io {

class IInputSource {
public:
    virtual std::string readLine() = 0;
};

}
