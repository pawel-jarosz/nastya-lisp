//
// Created by caedus on 21.12.2020.
//

#include "Modules/ModuleRegistry.hpp"

namespace nastya::modules {

ModuleRegistry& ModuleRegistry::registerModule(const IModule& module) {
    m_modules.try_emplace(module.getModuleName(), module);
    return *this;
}

std::vector<std::string> ModuleRegistry::getAvailableModules() const {
    std::vector<std::string> modules;
    for (auto [key, value]: m_modules) {
        modules.emplace_back(std::move(key));
    }
    return modules;
}

bool ModuleRegistry::isAvailableFunction(const std::string& function) {
    return false;
}

    runtime::IEvaluator &ModuleRegistry::getFunction(std::string string) const {
        return m_modules.at("Lists").getFunction(string);
    }

}
