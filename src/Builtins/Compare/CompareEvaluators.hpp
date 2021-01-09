//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::builtins::compare {

struct LowerEvaluator : public runtime::IEvaluator {
    std::string getName() const override {
        return "Lower";
    }

    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

struct LowerOrEqualEvaluator : public runtime::IEvaluator {
    std::string getName() const override {
        return "LowerOrEqual";
    }

    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

struct EqualEvaluator : public runtime::IEvaluator {
    std::string getName() const override {
        return "Equal";
    }

    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

struct GreaterOrEqualEvaluator : public runtime::IEvaluator {
    std::string getName() const override {
        return "GreaterOrEqual";
    }

    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const override;
};

struct GreaterEvaluator : public runtime::IEvaluator {
    std::string getName() const override {
        return "Greater";
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