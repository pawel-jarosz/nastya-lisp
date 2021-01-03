//
// Created by caedus on 20.12.2020.
//

#include "Modules/Module.hpp"
#include "Modules/ModuleException.hpp"

namespace nastya::modules {

Module::Module(std::string module_name) : m_module_name{module_name}
{
}

std::string Module::getModuleName() const
{
    return m_module_name;
}

bool Module::isFunctionAvailable(const std::string& function_name) const
{
    const auto function_it = m_functions.find(function_name);
    return (function_it != m_functions.end());
}

std::vector<std::string> Module::getFunctionsList() const
{
    std::vector<std::string> function_list;
    for (auto [key, value] : m_functions)
    {
        function_list.emplace_back(std::move(key));
    }
    return function_list;
}

runtime::IEvaluator& Module::getFunction(const std::string& function_name) const
{
    if (isFunctionAvailable(function_name))
    {
        return m_functions.at(function_name);
    }
    BUT_THROW(ModuleException, "Function is not available in module");
}

Module& Module::registerFunction(runtime::IEvaluator& evaluator)
{
    auto [it, return_value] = m_functions.try_emplace(evaluator.getName(), evaluator);
    if (not return_value)
    {
        BUT_THROW(ModuleException, "Function cannot be registered");
    }
    return *this;
}

}  // namespace nastya::modules
