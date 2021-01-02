//
// Created by caedus on 24.12.2020.
//

#pragma once

#include "LispExpression/ObjectStorage.hpp"

namespace nastya::runtime {

class IRuntimeEnvironment
{
public:
    virtual lisp::ObjectStorage run(const lisp::ObjectStorage& run) = 0;
};
}  // namespace nastya::runtime