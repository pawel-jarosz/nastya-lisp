//
// Created by caedus on 16.12.2020.
//
#pragma once

#include "TypeSystem/Types/LabelObject.hpp"
#include "TypeSystem/ObjectStorage.hpp"

namespace nastya::runtime {

class IMemory
{
public:
    virtual bool registerVariableOnHeap(const typesystem::LabelObject& variableName,
                                        const typesystem::ObjectStorage& objectStorage) = 0;
    virtual bool registerVariableOnStack(const typesystem::LabelObject& variableName,
                                         const typesystem::ObjectStorage& objectStorage) = 0;
    virtual const typesystem::ObjectStorage& getFromHeap(const typesystem::LabelObject& variableName) const = 0;
    virtual const typesystem::ObjectStorage& getFromStack(const typesystem::LabelObject& variableName) const = 0;
    virtual void pushStackFrame() = 0;
    virtual bool popStackFrame() = 0;
};

}  // namespace nastya::runtime