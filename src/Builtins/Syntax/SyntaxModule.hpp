//
// Created by caedus on 09.01.2021.
//

#pragma once

#include <map>

#include "Modules/Module.hpp"
#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::builtins::syntax {

class SyntaxModule : public modules::Module
{
public:
    static modules::IModule& getInstance();

private:
    SyntaxModule();
};

}  // namespace nastya::builtins::syntax
