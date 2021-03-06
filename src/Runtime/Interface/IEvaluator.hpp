//
// Created by caedus on 16.12.2020.
//

#pragma once

#include "TypeSystem/Types/ListObject.hpp"

#include "IMachine.hpp"
#include "Runtime/Interface/IMemory.hpp"
#include "TypeSystem/ObjectStorage.hpp"

namespace nastya::runtime {

class IEvaluator
{
public:
    virtual ~IEvaluator() = default;
    virtual std::string getName() const = 0;
    virtual typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                                  IMachine& vm) const = 0;
    virtual typesystem::ObjectStorage evaluate(IMemory& memory, const typesystem::ObjectStorage& object) const = 0;
    virtual void postExecute(IMachine& vm) const = 0;
};

}  // namespace nastya::runtime
