//
// Created by caedus on 22.12.2020.
//

#pragma once

#include "Modules/Interface/IModuleRegistry.hpp"
#include "Runtime/Interface/IMemory.hpp"
#include "Runtime/Interface/IRuntimeEnvironment.hpp"

namespace nastya::vm {

class Machine
: public runtime::IMemory
, public runtime::IRuntimeEnvironment
{
public:
    Machine(const modules::IModuleRegistry& m_modules);
    lisp::ObjectStorage run(const lisp::ObjectStorage& list) override;
private:
    const modules::IModuleRegistry& m_modules;
};

}  // namespace nastya::vm