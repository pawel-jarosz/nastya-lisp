//
// Created by caedus on 20.12.2020.
//

#pragma once

#include "Modules/Interface/IModule.hpp"

#include <map>

namespace nastya::modules {

class Module : public IModule {
public:
    explicit Module(std::string module_name);
    std::string getModuleName() const override;
    bool isFunctionAvailable(const std::string& function_name) const override;
    std::vector<std::string> getFunctionsList() const override;
    runtime::IEvaluator& getFunction(const std::string& function_name) const override;
    Module& registerFunction(runtime::IEvaluator& evaluator);
private:
    std::string m_module_name;
    std::map<std::string, runtime::IEvaluator&> m_functions;
};

}
