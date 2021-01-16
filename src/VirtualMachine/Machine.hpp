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
    bool registerVariableOnHeap(const lisp::typesystem::LabelObject& variableName,
                                const lisp::ObjectStorage& objectStorage) override;
    const lisp::ObjectStorage& getFromHeap(const lisp::typesystem::LabelObject& variableName) const override;
    bool isSymbolAvailable(const lisp::ObjectStorage& label) const;
private:
    const modules::IModuleRegistry& m_modules;
    const IArgumentPreparationManager& m_preparation_manager;
    std::map<std::string, lisp::ObjectStorage> m_heap;
};

}  // namespace nastya::vm