//
// Created by caedus on 06.01.2021.
//

#pragma once

#include <gmock/gmock.h>

#include "CLI/Interface/IIoFactory.hpp"

namespace nastya::cli::io {

class IoFactoryMock : public IIoFactory {
public:
    MOCK_METHOD(But::NotNullUnique<IInputSource>, create_input, (), (override));
    MOCK_METHOD(But::NotNullUnique<IOutputSink>, create_output, (), (override));
};

}

