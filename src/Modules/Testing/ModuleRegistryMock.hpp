//
// Created by caedus on 05.01.2021.
//

#pragma once

#include <gmock/gmock.h>

#include "Modules/Interface/IModuleRegistry.hpp"

namespace nastya::modules {

using namespace ::testing;

class ModuleRegistryMock : public IModuleRegistry
{
public:
    MOCK_METHOD(std::vector<std::string>, getAvailableModules, (), (const, override));
    MOCK_METHOD(bool, isAvailableFunction, (const std::string&), (override));
    MOCK_METHOD(runtime::IEvaluator&, getFunction, (std::string), (const, override));
};

}