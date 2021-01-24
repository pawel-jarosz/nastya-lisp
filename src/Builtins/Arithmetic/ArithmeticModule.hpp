//
// Created by caedus on 23.01.2021.
//

#pragma once

#include "Modules/Module.hpp"
#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::builtins::arithmetic {

class ArithmeticModule : public modules::Module
{
public:
    static modules::IModule& getInstance();

private:
    ArithmeticModule();
};

}  // namespace nastya::builtins::arithmetic
