//
// Created by caedus on 21.12.2020.
//

#pragma once

#include <string>

#include "Modules/ModuleBuilder.hpp"
#include "Builtins/Compare/CompareEvaluators.hpp"

namespace nastya::builtins::compare {

const std::string MODULE_NAME = "Lang.Compare";
using Builder = modules::ModuleBuilder<LowerEvaluator, LowerOrEqualEvaluator, EqualEvaluator,
    GreaterOrEqualEvaluator, GreaterEvaluator, CompareEvaluator>;

inline std::unique_ptr<modules::IModuleBuilder> create_module_builder()
{
    auto builder = std::make_unique<Builder>(MODULE_NAME);
    return std::unique_ptr<modules::IModuleBuilder>(builder.release());
}

}  // namespace nastya::builtins::compare
