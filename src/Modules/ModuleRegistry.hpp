//
// Created by caedus on 21.12.2020.
//

#pragma once

#include <map>

#include "Modules/Interface/IModuleRegistry.hpp"

namespace nastya::modules {

class ModuleRegistry : public IModuleRegistry
{
public:
    ModuleRegistry() = default;
    ModuleRegistry& registerModule(const IModule& module);
    std::vector<std::string> getAvailableModules() const override;
    bool isAvailableFunction(const std::string& function) override;
    runtime::IEvaluator& getFunction(std::string string) const override;
private:
    std::map<std::string, const IModule&> m_modules;
};

}  // namespace nastya::modules
