//
// Created by caedus on 02.01.2021.
//

#include "ConsoleEvaluators.hpp"
#include "ConsoleModule.hpp"

namespace nastya::cli::module {

void initializeModule(ConsoleModule& module, interface::IConsoleManager& console)
{
    static ShutdownEvaluator shutdown(console);
    module.registerFunction(shutdown);
}

ConsoleModule::ConsoleModule() : Module("CLI.App")
{
}

modules::IModule& ConsoleModule::getInstance(interface::IConsoleManager& console)
{
    static bool initialized = false;
    static ConsoleModule module;
    if (not initialized)
    {
        initializeModule(module, console);
        initialized = true;
    }
    return module;
}

}  // namespace nastya::cli::module
