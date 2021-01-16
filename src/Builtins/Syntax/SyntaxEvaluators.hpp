//
// Created by caedus on 09.01.2021.
//

#pragma once

#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::builtins::syntax {

struct IfEvaluator : public runtime::IEvaluator
{
    std::string getName() const override
    {
        return "If";
    }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
};

struct CondEvaluator : public runtime::IEvaluator
{
    std::string getName() const override
    {
        return "Cond";
    }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
};


}  // namespace nastya::builtins::syntax
