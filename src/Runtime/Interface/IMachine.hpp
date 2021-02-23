//
// Created by caedus on 06.01.2021.
//

#pragma once

#include "Runtime/Interface/IMemory.hpp"
#include "Runtime/Interface/IRuntimeEnvironment.hpp"
#include "TypeSystem/ObjectStorage.hpp"

namespace nastya::runtime {

class IMachine
: public runtime::IMemory
, public runtime::IRuntimeEnvironment {
public:
    virtual ~IMachine() = default;
};

}