//
// Created by caedus on 24.12.2020.
//

#pragma once

#include "TypeSystem/ObjectStorage.hpp"

namespace nastya::runtime {

class IRuntimeEnvironment
{
public:
    virtual typesystem::ObjectStorage run(const typesystem::ObjectStorage& run) = 0;
};
}  // namespace nastya::runtime