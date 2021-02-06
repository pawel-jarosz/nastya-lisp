//
// Created by caedus on 04.02.2021.
//

#pragma once

#include "Modules/Interface/IModule.hpp"

namespace nastya::modules {
class IModuleBuilder {
public:
    virtual ~IModuleBuilder() = default;
    virtual std::unique_ptr<IModule> build() = 0;
};
}
