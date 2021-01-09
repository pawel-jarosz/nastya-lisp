//
// Created by caedus on 21.12.2020.
//

#include "Builtins/Compare/CompareEvaluators.hpp"
#include "Builtins/Compare/CompareModule.hpp"

namespace nastya::builtins::compare {

void initializeModule(CompareModule& module)
{
    static EqualEvaluator equal;
    static CompareEvaluator compare;
    module.registerFunction(equal).registerFunction(compare);
}

CompareModule::CompareModule() : Module("Lang.Compare")
{
}

modules::IModule& CompareModule::getInstance()
{
    static bool initialized = false;
    static CompareModule module;
    if (not initialized)
    {
        initializeModule(module);
        initialized = true;
    }
    return module;
}

}  // namespace nastya::builtins::compare
