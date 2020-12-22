//
// Created by caedus on 20.12.2020.
//

#include "Modules/Module.hpp"

#include <iostream>

namespace nastya::modules {

Module::Module(std::string module_name) : m_module_name{module_name} {

}

std::string Module::getModuleName() const {
    return m_module_name;
}

bool Module::isFunctionAvailable(const std::string& function_name) const {
    const auto function_it = m_functions.find(function_name);
    return (function_it != m_functions.end());
}

std::vector<std::string> Module::getFunctionsList() const {
    std::vector<std::string> function_list;
    for (auto [key, value]: m_functions) {
        function_list.emplace_back(std::move(key));
    }
    return function_list;
}

runtime::IEvaluator& Module::getFunction(const std::string& function_name) const {
    // TODO: check if is not available
    if (isFunctionAvailable(function_name)) {
        return m_functions.at(function_name);
    }
    // add throwing exception
    throw;
}

Module& Module::registerFunction(runtime::IEvaluator& evaluator) {
    auto [it, return_value] = m_functions.try_emplace(evaluator.getName(), evaluator);
    if (not return_value) {
    }
    // verify if it was successfully emplaced;
    return *this;
}

}
