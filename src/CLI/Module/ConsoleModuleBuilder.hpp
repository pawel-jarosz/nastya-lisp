//
// Created by caedus on 02.01.2021.
//

#pragma once

#include "Modules/ModuleRegistry.hpp"
#include "CLI/Interface/IConsoleManager.hpp"

namespace nastya::cli::module {

class ConsoleModuleBuilder {
public:
    ConsoleModuleBuilder(modules::ModuleRegistry& registry, interface::IConsoleManager& console);
    void build() const;
private:
    modules::ModuleRegistry& m_registry;
    interface::IConsoleManager& m_console;
};

}
