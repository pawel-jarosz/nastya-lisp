//
// Created by caedus on 06.02.2021.
//

#pragma once

#include "Builtins/Interface/IBuiltinsModuleFactory.hpp"

namespace nastya::builtins {

class BuiltinsModulesFactory : public IBuiltinsModuleFactory{
public:
    BuiltinsModulesFactory() = default;
    std::unique_ptr<modules::IModule> createSyntax() const override;
    std::unique_ptr<modules::IModule> createLists() const override;
    std::unique_ptr<modules::IModule> createCompare() const override;
    std::unique_ptr<modules::IModule> createArithmetic() const override;
};

}
