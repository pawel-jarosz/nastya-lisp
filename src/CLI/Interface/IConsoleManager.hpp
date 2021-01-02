//
// Created by caedus on 02.01.2021.
//

#pragma once

namespace nastya::cli::interface {

class IConsoleManager
{
public:
    virtual ~IConsoleManager() = default;
    virtual int run() = 0;
    virtual void shutdown() = 0;
};

}  // namespace nastya::cli::interface