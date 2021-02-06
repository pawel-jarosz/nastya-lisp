//
// Created by caedus on 21.12.2020.
//

#pragma once

#include <string>

#include "Modules/ModuleBuilder.hpp"
#include "Builtins/Lists/ListsEvaluators.hpp"

namespace nastya::builtins::lists {

const std::string MODULE_NAME = "Lang.Lists";
using Builder = modules::ModuleBuilder<HeadEvaluator, TailEvaluator, QuoteEvaluator>;

inline std::unique_ptr<modules::IModuleBuilder> create_module_builder()
{
    auto builder = std::make_unique<Builder>(MODULE_NAME);
    return std::unique_ptr<modules::IModuleBuilder>(builder.release());
}

}  // namespace nastya::builtins::lists
