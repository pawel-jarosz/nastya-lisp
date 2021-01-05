//
// Created by caedus on 05.01.2021.
//
#pragma once

#include <map>

#include "Modules/Interface/IModule.hpp"

namespace nastya::modules {

class IModuleRegistry
{
public:
    ~IModuleRegistry() = default;
    virtual std::vector<std::string> getAvailableModules() const = 0;
    virtual bool isAvailableFunction(const std::string& function) = 0;
    virtual runtime::IEvaluator& getFunction(std::string string) const = 0;
};

}
