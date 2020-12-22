//
// Created by caedus on 21.12.2020.
//

#include "Builtins/Lists/ListsModule.hpp"
#include "Builtins/Lists/ListsEvaluators.hpp"

namespace nastya::builtins::lists {

void initializeModule(ListsModule& module) {
    static HeadEvaluator head;
    static TailEvaluator tail;
    module
        .registerFunction(head)
        .registerFunction(tail);
}


ListsModule::ListsModule() : Module("Lists") {}

modules::IModule& ListsModule::getInstance() {
    static bool initialized = false;
    static ListsModule module;
    if (not initialized) {
        initializeModule(module);
        initialized = true;
    }
    return module;
}


}
