//
// Created by caedus on 21.12.2020.
//

#pragma once

#include "Modules/AbstractModule.hpp"
#include "Runtime/Interface/IEvaluator.hpp"

#include <map>

namespace nastya::builtins::lists {

class ListsModule : public modules::AbstractModule {
public:
    ListsModule& getInstance();
    ListsModule& registerEvaluator(runtime::IEvaluator& evaluator);
private:
    ListsModule();
    std::map<std::string, runtime::IEvaluator&> m_methods;
};

}
