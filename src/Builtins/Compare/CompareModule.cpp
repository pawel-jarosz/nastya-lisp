//
// Created by caedus on 21.12.2020.
//

#include "Builtins/Compare/CompareEvaluators.hpp"
#include "Builtins/Compare/CompareModule.hpp"

namespace nastya::builtins::compare {

void initializeModule(CompareModule& module)
{
    static LowerEvaluator lower;
    static LowerOrEqualEvaluator lower_or_equal;
    static EqualEvaluator equal;
    static GreaterOrEqualEvaluator greater_or_equal;
    static GreaterEvaluator greater;
    static CompareEvaluator compare;
    module.registerFunction(compare)
        .registerFunction(lower)
        .registerFunction(lower_or_equal)
        .registerFunction(equal)
        .registerFunction(greater_or_equal)
        .registerFunction(greater);
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
