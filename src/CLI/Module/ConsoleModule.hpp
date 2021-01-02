//
// Created by caedus on 02.01.2021.
//

#include "Modules/Module.hpp"
#include "Runtime/Interface/IEvaluator.hpp"
#include "CLI/Interface/IConsoleManager.hpp"

#include <map>

namespace nastya::cli::module {

class ConsoleModule : public modules::Module
{
public:
    static modules::IModule& getInstance(interface::IConsoleManager& console);

private:
    ConsoleModule();
    std::map<std::string, runtime::IEvaluator&> m_methods;
};

}
