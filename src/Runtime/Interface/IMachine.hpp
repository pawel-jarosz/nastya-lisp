//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "LispExpression/ObjectStorage.hpp"
#include "Runtime/Interface/IMemory.hpp"
#include "Runtime/Interface/IRuntimeEnvironment.hpp"

namespace nastya::runtime {

class IMachine
: public runtime::IMemory
, public runtime::IRuntimeEnvironment {
public:
    virtual ~IMachine() = default;
};

}