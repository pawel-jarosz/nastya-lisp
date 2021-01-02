//
// Created by caedus on 02.01.2021.
//

#include "ConsoleModule.hpp"
#include "ConsoleModuleBuilder.hpp"

namespace nastya::cli::module {

ConsoleModuleBuilder::ConsoleModuleBuilder(modules::ModuleRegistry& registry, interface::IConsoleManager& console)
: m_registry{registry}, m_console{console}
{
}

void ConsoleModuleBuilder::build() const
{
    m_registry.registerModule(ConsoleModule::getInstance(m_console));
}

}  // namespace nastya::cli::module