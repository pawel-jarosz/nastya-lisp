//
// Created by caedus on 16.01.2021.
//

#pragma once

#include "VirtualMachine/Interface/IArgumentPreparationStrategy.hpp"

namespace nastya::vm {

class DefineStrategy : public IArgumentPreparationStrategy {
public:
    std::string getName() const override { return "Define"; }
    lisp::ObjectStorage extract_arguments(const lisp::typesystem::ListObject& object,
                                          vm::IMachine& vm) const override;
};

}
