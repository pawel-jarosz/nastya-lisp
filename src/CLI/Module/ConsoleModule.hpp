//
// Created by caedus on 02.01.2021.
//

#include <map>

#include "CLI/Interface/IConsoleManager.hpp"
#include "Modules/Module.hpp"
#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::cli::module {

struct ConsoleModule : public modules::Module
{
public:
    ConsoleModule();
};

std::unique_ptr<modules::IModule> create_module(cli::interface::IConsoleManager& console);

}  // namespace nastya::cli::module
