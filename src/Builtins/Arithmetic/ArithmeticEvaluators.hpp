//
// Created by caedus on 23.01.2021.
//

#pragma once

#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::builtins::arithmetic {

struct AddEvaluator : public runtime::IEvaluator
{
    std::string getName() const override
    {
        return "+";
    }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
};

struct SubtractionEvaluator : public runtime::IEvaluator
{
    std::string getName() const override
    {
        return "-";
    }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
};

struct MultiplicationEvaluator : public runtime::IEvaluator
{
    std::string getName() const override
    {
        return "*";
    }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
};

struct DivisionEvaluator : public runtime::IEvaluator
{
    std::string getName() const override
    {
        return "/";
    }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
};

struct ModuloEvaluator : public runtime::IEvaluator
{
    std::string getName() const override
    {
        return "%";
    }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
};

struct PowerEvaluator : public runtime::IEvaluator
{
    std::string getName() const override
    {
        return "-";
    }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
};



}