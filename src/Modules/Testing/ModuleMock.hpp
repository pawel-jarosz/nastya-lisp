//
// Created by caedus on 21.12.2020.
//

#pragma once

#include "Modules/Interface/IModule.hpp"

#include <gmock/gmock.h>

namespace nastya::modules::testing {

using namespace ::testing;

class ModuleMock : public IModule {
public:
    MOCK_METHOD(std::string, getModuleName, (), (const, override));
    MOCK_METHOD(std::vector<std::string>, getFunctionsList, (), (const, override));
    MOCK_METHOD(bool, isFunctionAvailable, (const std::string&), (const, override));
    MOCK_METHOD(runtime::IEvaluator&, getFunction, (const std::string&), (const, override));
};

}
