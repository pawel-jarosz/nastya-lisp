//
// Created by caedus on 10.01.2021.
//

#pragma once

#include "VirtualMachine/Interface/IArgumentPreparationManager.hpp"
#include <map>

namespace nastya::vm {

class ArgumentPreparationManager : public IArgumentPreparationManager {
public:
    ArgumentPreparationManager() = default;
    static void init(ArgumentPreparationManager& init);
    void registerStrategy(std::unique_ptr<IArgumentPreparationStrategy> strategy) override;
    const IArgumentPreparationStrategy& getStrategy(const std::string& strategy_name) const override;
private:
    std::map<std::string, std::unique_ptr<IArgumentPreparationStrategy>> m_strategies;
};

}
