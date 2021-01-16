//
// Created by caedus on 16.12.2020.
//
#pragma once

#include "LispExpression/TypeSystem/LabelObject.hpp"
#include "LispExpression/ObjectStorage.hpp"

namespace nastya::runtime {

class IMemory
{
public:
    virtual bool registerVariableOnHeap(const lisp::typesystem::LabelObject& variableName,
                                        const lisp::ObjectStorage& objectStorage) = 0;
    virtual const lisp::ObjectStorage& getFromHeap(const lisp::typesystem::LabelObject& variableName) const = 0;
};

}  // namespace nastya::runtime