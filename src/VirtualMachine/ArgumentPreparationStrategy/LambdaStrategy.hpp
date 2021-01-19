//
// Created by caedus on 19.01.2021.
//

#pragma once

#include "VirtualMachine/Interface/IArgumentPreparationStrategy.hpp"

namespace nastya::vm {

class LambdaStrategy : public IArgumentPreparationStrategy {
public:
    std::string getName() const override { return "Lambda"; }
    lisp::ObjectStorage extract_arguments(const lisp::typesystem::ListObject& object,
                                          vm::IMachine& vm) const override;
};

}

