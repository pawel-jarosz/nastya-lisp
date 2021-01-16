//
// Created by caedus on 10.01.2021.
//

#pragma once

#include "LispExpression/TypeSystem/ListObject.hpp"
#include "VirtualMachine/Interface/IMachine.hpp"
#include "LispExpression/ObjectStorage.hpp"

namespace nastya::vm {

class IArgumentPreparationStrategy {
public:
    virtual std::string getName() const = 0;
    virtual lisp::ObjectStorage extract_arguments(const lisp::typesystem::ListObject& object,
                                                  vm::IMachine& vm) const = 0;
};

}