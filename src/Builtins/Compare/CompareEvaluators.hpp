//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "Runtime/GenericEvaluator.hpp"
#include "Runtime/GenericEvaluatorFactory.hpp"

namespace nastya::builtins::compare {

class LowerEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<LowerEvaluator> {
public:
    LowerEvaluator() : runtime::GenericEvaluator{"Lower"} {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

class LowerOrEqualEvaluator : public runtime::GenericEvaluator
                            , public runtime::GenericEvaluatorFactory<LowerOrEqualEvaluator> {
public:
    LowerOrEqualEvaluator() : runtime::GenericEvaluator{"LowerOrEqual"} {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

class EqualEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<EqualEvaluator> {
public:
    EqualEvaluator() : runtime::GenericEvaluator{"Equal"} {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

class GreaterOrEqualEvaluator : public runtime::GenericEvaluator
                              , public runtime::GenericEvaluatorFactory<GreaterOrEqualEvaluator> {
public:
    GreaterOrEqualEvaluator() : runtime::GenericEvaluator{"GreaterOrEqual"} {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

class GreaterEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<GreaterEvaluator> {
public:
    GreaterEvaluator() : runtime::GenericEvaluator{"Greater"} {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

class CompareEvaluator : public runtime::GenericEvaluator, public runtime::GenericEvaluatorFactory<CompareEvaluator> {
public:
    CompareEvaluator() : runtime::GenericEvaluator{"Compare"} {}
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

}