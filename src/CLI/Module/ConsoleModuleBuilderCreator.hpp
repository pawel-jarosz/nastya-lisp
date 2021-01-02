//
// Created by caedus on 02.01.2021.
//

#pragma once

#include "ConsoleModuleBuilder.hpp"

namespace nastya::cli::module {

class ConsoleModuleBuilderCreator {
public:
    ConsoleModuleBuilderCreator() = default;
    inline ConsoleModuleBuilder create(modules::ModuleRegistry& registry, interface::IConsoleManager& console) {
        return ConsoleModuleBuilder(registry, console);
    }
};
};