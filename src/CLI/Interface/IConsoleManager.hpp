//
// Created by caedus on 02.01.2021.
//

#pragma once

namespace nastya::cli::interface {

class IConsoleManager {
public:
    ~IConsoleManager();
    virtual int run() = 0;
    virtual void shutdown() = 0;
};

}