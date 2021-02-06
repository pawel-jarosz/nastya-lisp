//
// Created by caedus on 06.02.2021.
//

#pragma once

#include "Modules/Interface/IModule.hpp"

namespace nastya::builtins {

class IBuiltinsModuleFactory
{
public:
    virtual std::unique_ptr<modules::IModule> createSyntax() const = 0;
    virtual std::unique_ptr<modules::IModule> createLists() const = 0;
    virtual std::unique_ptr<modules::IModule> createCompare() const = 0;
    virtual std::unique_ptr<modules::IModule> createArithmetic() const = 0;
};

}