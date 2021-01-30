//
// Created by caedus on 21.12.2020.
//

#pragma once

#include <Runtime/GenericEvaluator.hpp>

#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::builtins::lists {

class HeadEvaluator : public runtime::GenericEvaluator
{
public:
    HeadEvaluator() : runtime::GenericEvaluator{"Head"} {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

class TailEvaluator : public runtime::GenericEvaluator
{
public:
    TailEvaluator() : runtime::GenericEvaluator{"Tail"} {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

class QuoteEvaluator : public runtime::GenericEvaluator
{
public:
    QuoteEvaluator() : runtime::GenericEvaluator{"Quote"} {}
    lisp::ObjectStorage preExecute(const lisp::typesystem::ListObject& object,
                                   runtime::IMachine& vm) const override;
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

}  // namespace nastya::builtins::lists
