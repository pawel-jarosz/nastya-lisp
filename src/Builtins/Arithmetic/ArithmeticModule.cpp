//
// Created by caedus on 23.01.2021.
//

#include "Builtins/Arithmetic/ArithmeticEvaluators.hpp"
#include "Builtins/Arithmetic/ArithmeticModule.hpp"

namespace nastya::builtins::arithmetic {

void initializeModule(ArithmeticModule& module)
{
    static AddEvaluator add;
    static SubtractionEvaluator subtraction;
    module.registerFunction(add)
        .registerFunction(subtraction);
}

ArithmeticModule::ArithmeticModule() : Module("Lang.Arithmetic")
{
}

modules::IModule& ArithmeticModule::getInstance()
{
    static bool initialized = false;
    static ArithmeticModule module;
    if (not initialized)
    {
        initializeModule(module);
        initialized = true;
    }
    return module;
}

}  // namespace nastya::builtins::arithmetic

