//
// Created by caedus on 16.12.2020.
//

#pragma once

#include <string>
#include <vector>

#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::modules {

class IModule
{
public:
    virtual std::string getModuleName() const = 0;
    virtual std::vector<std::string> getFunctionsList() const = 0;
    virtual bool isFunctionAvailable(const std::string& function) const = 0;
    virtual runtime::IEvaluator& getFunction(const std::string& function_name) const = 0;
};

}  // namespace nastya::modules
