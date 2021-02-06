//
// Created by caedus on 02.01.2021.
//

#include "ConsoleModule.hpp"
#include "CLI/Module/ConsoleEvaluators.hpp"

namespace nastya::cli::module {

ConsoleModule::ConsoleModule() : Module("CLI.App")
{
}

std::unique_ptr<modules::IModule> create_module(cli::interface::IConsoleManager& console) {
    auto module = std::make_unique<ConsoleModule>();
    module->registerFunction(std::unique_ptr<runtime::IEvaluator>(new ShutdownEvaluator(console)));
    std::unique_ptr<modules::IModule> result(module.release());
    return result;
}

}  // namespace nastya::cli::module
