//
// Created by caedus on 02.01.2021.
//

#include "CLI/Module/ConsoleModule.hpp"
#include "CLI/Module/ConsoleModuleBuilder.hpp"
#include "CLI/Module/ConsoleEvaluators.hpp"

namespace nastya::cli::module {

ConsoleModuleBuilder::ConsoleModuleBuilder(modules::ModuleRegistry& registry, interface::IConsoleManager& console)
: m_registry{registry}, m_console{console}
{
}

void ConsoleModuleBuilder::build() const
{
    auto module = std::make_unique<ConsoleModule>();
    module->registerFunction(std::unique_ptr<runtime::IEvaluator>(new ShutdownEvaluator(m_console)));
    m_registry.registerModule(std::unique_ptr<modules::IModule>(module.release()));
}

}  // namespace nastya::cli::module