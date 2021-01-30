//
// Created by caedus on 22.12.2020.
//

#pragma once

#include "Modules/Interface/IModuleRegistry.hpp"
#include "Runtime/Interface/IMachine.hpp"

#include <optional>
#include <vector>
#include <map>

namespace nastya::vm {

class Machine : public runtime::IMachine
{
public:
    Machine(const modules::IModuleRegistry& m_modules);
    lisp::ObjectStorage run(const lisp::ObjectStorage& list) override;
    bool isSymbolAvailable(const lisp::ObjectStorage& label) const;
    bool registerVariableOnHeap(const lisp::typesystem::LabelObject& variableName,
                                const lisp::ObjectStorage& objectStorage) override;
    const lisp::ObjectStorage& getFromHeap(const lisp::typesystem::LabelObject& variableName) const override;
    bool registerVariableOnStack(const lisp::typesystem::LabelObject& variableName,
                                 const lisp::ObjectStorage& objectStorage) override;
    const lisp::ObjectStorage& getFromStack(const lisp::typesystem::LabelObject& variableName) const override;
    void pushStackFrame() override;
    bool popStackFrame() override;
private:
    std::optional<lisp::ObjectStorage> computeLabel(const lisp::ObjectStorage& label) const;
    const modules::IModuleRegistry& m_modules;
    std::map<std::string, lisp::ObjectStorage> m_heap;
    std::vector<std::map<std::string, lisp::ObjectStorage>> m_stack;
};

}  // namespace nastya::vm