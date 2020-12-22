//
// Created by caedus on 22.12.2020.
//

#pragma once

#include "LispExpression/ObjectStorage.hpp"
#include "Runtime/Interface/IMemory.hpp"
#include "Modules/ModuleRegistry.hpp"

namespace nastya::executor {

class ExecutorEnvironment : public runtime::IMemory {
public:
    ExecutorEnvironment(const modules::ModuleRegistry& m_modules);
    lisp::ObjectStorage evaluate(const lisp::ObjectStorage& list);
private:
    modules::ModuleRegistry m_modules;
};

}