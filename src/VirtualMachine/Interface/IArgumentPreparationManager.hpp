//
// Created by caedus on 10.01.2021.
//

#pragma once

#include "VirtualMachine/Interface/IArgumentPreparationStrategy.hpp"

namespace nastya::vm {

class IArgumentPreparationManager {
public:
    virtual void registerStrategy(std::unique_ptr<IArgumentPreparationStrategy> strategy) = 0;
    virtual const IArgumentPreparationStrategy& getStrategy(const std::string& strategy_name) const = 0;
};

}