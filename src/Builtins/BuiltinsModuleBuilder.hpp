//
// Created by caedus on 20.12.2020.
//

#pragma once

#include "Modules/ModuleRegistry.hpp"

namespace nastya::builtins {

class BuiltinsModuleBuilder
{
public:
    BuiltinsModuleBuilder(modules::ModuleRegistry& registry);
    void build() const;

private:
    modules::ModuleRegistry& m_registry;
};

}  // namespace nastya::builtins
