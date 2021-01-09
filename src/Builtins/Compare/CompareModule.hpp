//
// Created by caedus on 21.12.2020.
//

#pragma once

#include <map>

#include "Modules/Module.hpp"
#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::builtins::compare {

class CompareModule : public modules::Module
{
public:
    static modules::IModule& getInstance();

private:
    CompareModule();
};

}  // namespace nastya::builtins::compare
