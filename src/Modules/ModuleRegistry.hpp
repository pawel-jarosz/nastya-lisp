//
// Created by caedus on 21.12.2020.
//

#pragma once

#include "Modules/Interface/IModule.hpp"

#include <map>

namespace nastya::modules {

class ModuleRegistry {
public:
    ModuleRegistry() = default;
    ModuleRegistry& registerModule(const IModule& module);

private:
    std::map<std::string, const IModule&> m_modules;
};

}

