//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "CLI/Interface/IInputSource.hpp"
#include "CLI/Interface/IOutputSink.hpp"

#include <But/NotNull.hpp>

namespace nastya::cli::io {

class IIoFactory {
public:
    virtual ~IIoFactory() = default;
    virtual But::NotNullUnique<IInputSource> create_input() = 0;
    virtual But::NotNullUnique<IOutputSink> create_output() = 0;
};

}

