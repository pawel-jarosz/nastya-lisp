//
// Created by caedus on 16.12.2020.
//

#pragma once

#include "Runtime/Interface/IEvaluator.hpp"

#include <vector>
#include <string>

namespace nastya::modules {

class IModule {
public:
    virtual std::string getModuleName() const = 0;
    virtual std::vector<std::string> getFunctionsList() const = 0;
    virtual bool hasFunction(const std::string& function) const = 0;
};

}
