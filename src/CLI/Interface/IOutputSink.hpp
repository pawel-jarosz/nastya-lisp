//
// Created by caedus on 06.01.2021.
//

#pragma once

#include <string>

namespace nastya::cli::io {

class IOutputSink {
public:
    virtual void writeLine(std::string line) = 0;
    virtual void write(std::string line) = 0;
};

}
