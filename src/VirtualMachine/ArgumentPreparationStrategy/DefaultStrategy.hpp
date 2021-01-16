//
// Created by caedus on 10.01.2021.
//

#pragma once

#include "VirtualMachine/Interface/IArgumentPreparationStrategy.hpp"

namespace nastya::vm {

class DefaultStrategy : public IArgumentPreparationStrategy {
public:
    std::string getName() const override { return "Default"; }
    lisp::ObjectStorage extract_arguments(const lisp::typesystem::ListObject& object,
                                          vm::IMachine& vm) const override;
};

}

