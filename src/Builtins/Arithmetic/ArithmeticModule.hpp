//
// Created by caedus on 23.01.2021.
//

#pragma once

#include <string>

#include "Modules/ModuleBuilder.hpp"
#include "Builtins/Arithmetic/ArithmeticEvaluators.hpp"

namespace nastya::builtins::arithmetic {

const std::string MODULE_NAME = "Lang.Arithmetic";
using Builder = modules::ModuleBuilder<AddEvaluator, SubtractionEvaluator, MultiplyEvaluator, DivisionEvaluator>;

inline std::unique_ptr<modules::IModuleBuilder> create_module_builder()
{
    auto builder = std::make_unique<Builder>(MODULE_NAME);
    return std::unique_ptr<modules::IModuleBuilder>(builder.release());
}

}  // namespace nastya::builtins::arithmetic
