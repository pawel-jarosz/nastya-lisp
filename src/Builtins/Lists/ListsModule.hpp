//
// Created by caedus on 21.12.2020.
//

#pragma once

#include <map>

#include "Modules/Module.hpp"
#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::builtins::lists {

class ListsModule : public modules::Module
{
public:
    static modules::IModule& getInstance();

private:
    ListsModule();
    std::map<std::string, runtime::IEvaluator&> m_methods;
};

}  // namespace nastya::builtins::lists
