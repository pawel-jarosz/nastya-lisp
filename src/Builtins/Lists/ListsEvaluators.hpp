//
// Created by caedus on 21.12.2020.
//

#pragma once

#include <Runtime/GenericEvaluator.hpp>
#include "Runtime/GenericEvaluatorFactory.hpp"

namespace nastya::builtins::lists {

class HeadEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<HeadEvaluator>
{
public:
    HeadEvaluator() : runtime::GenericEvaluator{"Head"} {}
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;
};

class TailEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<TailEvaluator>
{
public:
    TailEvaluator() : runtime::GenericEvaluator{"Tail"} {}
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;
};

class QuoteEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<QuoteEvaluator>
{
public:
    QuoteEvaluator() : runtime::GenericEvaluator{"Quote"} {}
    typesystem::ObjectStorage preExecute(const typesystem::ListObject& object,
                                   runtime::IMachine& vm) const override;
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;
};

}  // namespace nastya::builtins::lists
