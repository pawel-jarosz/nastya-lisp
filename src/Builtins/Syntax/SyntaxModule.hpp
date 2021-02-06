//
// Created by caedus on 09.01.2021.
//

#pragma once
#include <string>

#include "Modules/ModuleBuilder.hpp"
#include "Builtins/Syntax/SyntaxEvaluators.hpp"

namespace nastya::builtins::syntax {

const std::string MODULE_NAME = "Lang.Syntax";
using Builder = modules::ModuleBuilder<IfEvaluator,
    CondEvaluator,
    DefineEvaluator,
    LetInEvaluator,
    LambdaEvaluator>;

inline std::unique_ptr<modules::IModuleBuilder> create_module_builder() {
    auto builder = std::make_unique<Builder>(MODULE_NAME);
    return std::unique_ptr<modules::IModuleBuilder>(builder.release());
}

}  // namespace nastya::builtins::syntax
