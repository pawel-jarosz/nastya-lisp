//
// Created by caedus on 20.12.2020.
//

#pragma once

#include <map>

#include "Modules/Interface/IModule.hpp"

namespace nastya::modules {

class Module : public IModule
{
public:
    explicit Module(std::string module_name);
    std::string getModuleName() const override;
    bool isFunctionAvailable(const std::string& function_name) const override;
    std::vector<std::string> getFunctionsList() const override;
    runtime::IEvaluator& getFunction(const std::string& function_name) const override;
    Module& registerFunction(std::unique_ptr<runtime::IEvaluator> evaluator);

private:
    std::string m_module_name;
    std::map<std::string, std::unique_ptr<runtime::IEvaluator>> m_functions;
};

}  // namespace nastya::modules
