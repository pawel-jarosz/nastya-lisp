//
// Created by caedus on 21.12.2020.
//

#include "Builtins/Lists/ListsModule.hpp"
#include "Builtins/Lists/ListsEvaluators.hpp"

namespace nastya::builtins::lists {

ListsModule::ListsModule() : Module("Lists") {}

ListsModule& ListsModule::registerEvaluator(runtime::IEvaluator& evaluator) {
    m_methods[evaluator.getName()] = evaluator;
}

ListsModule& ListsModule::getInstance() {
    static bool initialized = false;
    static ListsModule module;
    if (not initialized) {
        initializeModule(*this);
        initialized = true;
    }
    return module;
}

void initializeModule(ListsModule& module) {
    static HeadEvaluator head;
    static TailEvaluator tail;
    module
    .registerEvaluator(head)
    .registerEvaluator(tail);
}

}
