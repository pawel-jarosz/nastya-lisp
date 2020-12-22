//
// Created by caedus on 21.12.2020.
//

#pragma once

#include "Runtime/Interface/IEvaluator.hpp"

namespace nastya::builtins::lists {

struct HeadEvaluator : public runtime::IEvaluator {
    std::string getName() const  override { return "Head"; }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
};

struct TailEvaluator : public runtime::IEvaluator {
    std::string getName() const override { return "Tail"; }
    lisp::ObjectStorage evaluate(runtime::IMemory& memory, const lisp::ObjectStorage& object) const;
};

}
