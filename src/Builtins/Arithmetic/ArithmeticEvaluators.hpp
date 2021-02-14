//
// Created by caedus on 23.01.2021.
//

#pragma once

#include "Runtime/GenericEvaluatorFactory.hpp"
#include "Runtime/GenericEvaluator.hpp"

namespace nastya::builtins::arithmetic {

class AddEvaluator : public runtime::GenericEvaluator
                   , public runtime::GenericEvaluatorFactory<AddEvaluator>
{
public:
    AddEvaluator() : runtime::GenericEvaluator{"+"} {}
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;
};

class SubtractionEvaluator : public runtime::GenericEvaluator
                           , public runtime::GenericEvaluatorFactory<SubtractionEvaluator>
{
public:
    SubtractionEvaluator() : runtime::GenericEvaluator{"-"} {}
    typesystem::ObjectStorage evaluate(runtime::IMemory& memory, const typesystem::ObjectStorage& object) const override;
};

}