//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::builtins::compare {

struct EqualEvaluator : public runtime::IEvaluator {
    std::string getName() const override {
        return "Equal";
    }

    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

struct CompareEvaluator : public runtime::IEvaluator {
    std::string getName() const override {
        return "Compare";
    }

    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

}