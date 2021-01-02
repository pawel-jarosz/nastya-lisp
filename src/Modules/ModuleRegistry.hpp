//
// Created by caedus on 21.12.2020.
//

#pragma once

#include <map>

#include "Modules/Interface/IModule.hpp"

namespace nastya::modules {

class ModuleRegistry
{
public:
    ModuleRegistry() = default;
    ModuleRegistry& registerModule(const IModule& module);
    std::vector<std::string> getAvailableModules() const;
    bool isAvailableFunction(const std::string& function);
    runtime::IEvaluator& getFunction(std::string string) const;

private:
    std::map<std::string, const IModule&> m_modules;
};

}  // namespace nastya::modules
