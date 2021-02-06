//
// Created by caedus on 02.01.2021.
//

#include "CLI/Module/ConsoleModule.hpp"
#include "CLI/Module/ConsoleModuleRegistration.hpp"

namespace nastya::cli::module {

ConsoleModuleRegistration::ConsoleModuleRegistration(modules::ModuleRegistry& registry, interface::IConsoleManager& console)
: m_registry{registry}, m_console{console}
{
}

void ConsoleModuleRegistration::build() const
{
    m_registry.registerModule(module::create_module(m_console));
}

}  // namespace nastya::cli::module