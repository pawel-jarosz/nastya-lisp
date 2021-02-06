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

}  // namespace nastya::cli::module
