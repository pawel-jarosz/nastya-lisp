//
// Created by caedus on 22.12.2020.
//

#pragma once

#include "Modules/Interface/IModuleRegistry.hpp"
#include "VirtualMachine/Interface/IMachine.hpp"

namespace nastya::vm {

class Machine : public IMachine
{
public:
    Machine(const modules::IModuleRegistry& m_modules);
    lisp::ObjectStorage run(const lisp::ObjectStorage& list) override;
private:
    const modules::IModuleRegistry& m_modules;
};

}  // namespace nastya::vm