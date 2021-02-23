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
    typesystem::ObjectStorage run(const typesystem::ObjectStorage& list) override;
    bool isSymbolAvailable(const typesystem::ObjectStorage& label) const;
    bool registerVariableOnHeap(const typesystem::LabelObject& variableName,
                                const typesystem::ObjectStorage& objectStorage) override;
    const typesystem::ObjectStorage& getFromHeap(const typesystem::LabelObject& variableName) const override;
    bool registerVariableOnStack(const typesystem::LabelObject& variableName,
                                 const typesystem::ObjectStorage& objectStorage) override;
    const typesystem::ObjectStorage& getFromStack(const typesystem::LabelObject& variableName) const override;
    void pushStackFrame() override;
    bool popStackFrame() override;
private:
    std::optional<typesystem::ObjectStorage> computeLabel(const typesystem::ObjectStorage& label) const;
    const modules::IModuleRegistry& m_modules;
    std::map<std::string, typesystem::ObjectStorage> m_heap;
    std::vector<std::map<std::string, typesystem::ObjectStorage>> m_stack;
};

}  // namespace nastya::vm