//
// Created by caedus on 22.12.2020.
//

#pragma once

#include "Runtime/Interface/IRuntimeEnvironment.hpp"
#include "Runtime/Interface/IMemory.hpp"
#include "Modules/ModuleRegistry.hpp"

namespace nastya::vm {

class Machine : public runtime::IMemory,
                public runtime::IRuntimeEnvironment {
public:
    Machine(const modules::ModuleRegistry& m_modules);
    lisp::ObjectStorage run(const lisp::ObjectStorage& list) override;
private:
    const modules::ModuleRegistry& m_modules;
};

}