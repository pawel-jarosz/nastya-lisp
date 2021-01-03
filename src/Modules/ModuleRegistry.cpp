//
// Created by caedus on 21.12.2020.
//

#include "Modules/ModuleException.hpp"
#include "Modules/ModuleRegistry.hpp"

namespace nastya::modules {

ModuleRegistry& ModuleRegistry::registerModule(const IModule& module)
{
    m_modules.try_emplace(module.getModuleName(), module);
    return *this;
}

std::vector<std::string> ModuleRegistry::getAvailableModules() const
{
    std::vector<std::string> modules;
    for (auto [key, value] : m_modules)
    {
        modules.emplace_back(std::move(key));
    }
    return modules;
}

bool ModuleRegistry::isAvailableFunction(const std::string& function_name)
{
    for (auto [module_name, module] : m_modules)
    {
        if (module.isFunctionAvailable(function_name))
        {
            return true;
        }
    }
}

runtime::IEvaluator& ModuleRegistry::getFunction(std::string function_name) const
{
    for (auto [module_name, module] : m_modules)
    {
        if (module.isFunctionAvailable(function_name))
        {
            return module.getFunction(function_name);
        }
    }
    BUT_THROW(ModuleException, "Function not found");
}

}  // namespace nastya::modules
