//
// Created by caedus on 20.12.2020.
//

#pragma once

#include "Modules/ModuleRegistry.hpp"
#include "Builtins/Interface/IBuiltinsModuleFactory.hpp"

namespace nastya::builtins {

class BuiltinsBuilder
{
public:
    BuiltinsBuilder(modules::ModuleRegistry& registry, IBuiltinsModuleFactory& factory);
    void build() const;

private:
    modules::ModuleRegistry& m_registry;
    IBuiltinsModuleFactory& m_factory;
};

}  // namespace nastya::builtins
