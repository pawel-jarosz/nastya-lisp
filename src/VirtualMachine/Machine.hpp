//
// Created by caedus on 22.12.2020.
//

#pragma once

#include "Modules/Interface/IModuleRegistry.hpp"
#include "VirtualMachine/Interface/IMachine.hpp"
#include "VirtualMachine/Interface/IArgumentPreparationManager.hpp"

namespace nastya::vm {

class Machine : public IMachine
{
public:
    Machine(const modules::IModuleRegistry& m_modules, const IArgumentPreparationManager& m_preparation_manager);
    lisp::ObjectStorage run(const lisp::ObjectStorage& list) override;
private:
    const modules::IModuleRegistry& m_modules;
    const IArgumentPreparationManager& m_preparation_manager;
};

}  // namespace nastya::vm