//
// Created by caedus on 09.01.2021.
//

#include "Builtins/Syntax/SyntaxEvaluators.hpp"
#include "Builtins/Syntax/SyntaxModule.hpp"

namespace nastya::builtins::syntax {

void initializeModule(SyntaxModule& module)
{
    static IfEvaluator if_command;
    static CondEvaluator cond;
    static DefineEvaluator define;
    static LetInEvaluator letIn;
    static LambdaEvaluator lambda;
    module.registerFunction(if_command)
          .registerFunction(cond)
          .registerFunction(define)
          .registerFunction(letIn)
          .registerFunction(lambda);
}

SyntaxModule::SyntaxModule() : Module("Lang.Syntax")
{
}

modules::IModule& SyntaxModule::getInstance()
{
    static bool initialized = false;
    static SyntaxModule module;
    if (not initialized)
    {
        initializeModule(module);
        initialized = true;
    }
    return module;
}

}  // namespace nastya::builtins::syntax
