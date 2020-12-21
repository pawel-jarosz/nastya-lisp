//
// Created by caedus on 21.12.2020.
//

#include "Modules/ModuleRegistry.hpp"

namespace nastya::modules {

ModuleRegistry& ModuleRegistry::registerModule(const IModule& module) {
    m_modules.try_emplace(module.getModuleName(), module);
    return *this;
}

}
