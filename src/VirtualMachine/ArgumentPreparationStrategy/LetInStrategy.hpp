//
// Created by caedus on 17.01.2021.
//

#pragma once

#include "VirtualMachine/Interface/IArgumentPreparationStrategy.hpp"

namespace nastya::vm {

class LetInStrategy : public IArgumentPreparationStrategy {
public:
    std::string getName() const override { return "Let"; }
    lisp::ObjectStorage extract_arguments(const lisp::typesystem::ListObject& object,
                                          vm::IMachine& vm) const override;
};

}
