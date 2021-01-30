//
// Created by caedus on 23.01.2021.
//

#pragma once

#include "Runtime/GenericEvaluator.hpp"

namespace nastya::builtins::arithmetic {

class AddEvaluator : public runtime::GenericEvaluator
{
public:
    AddEvaluator() : runtime::GenericEvaluator{"+"} {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

class SubtractionEvaluator : public runtime::GenericEvaluator
{
public:
    SubtractionEvaluator() : runtime::GenericEvaluator{"-"} {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

}