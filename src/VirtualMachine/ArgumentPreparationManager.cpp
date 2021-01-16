//
// Created by caedus on 10.01.2021.
//

#include "ArgumentPreparationManager.hpp"

#include "VirtualMachine/ArgumentPreparationStrategy/DefaultStrategy.hpp"
#include "VirtualMachine/ArgumentPreparationStrategy/QuoteStrategy.hpp"
#include "VirtualMachine/ArgumentPreparationStrategy/CondStrategy.hpp"

#include <utility>

namespace nastya::vm {

void ArgumentPreparationManager::init(ArgumentPreparationManager& manager)
{
    manager.registerStrategy(std::make_unique<DefaultStrategy>());
    manager.registerStrategy(std::make_unique<CondStrategy>());
    manager.registerStrategy(std::make_unique<QuoteStrategy>());
}

void ArgumentPreparationManager::registerStrategy(std::unique_ptr<IArgumentPreparationStrategy> strategy) {
    const auto name = strategy->getName();
    m_strategies.emplace(name, std::move(strategy));
}

const IArgumentPreparationStrategy&
ArgumentPreparationManager::getStrategy(const std::string& strategy_name) const {
    const auto it = m_strategies.find(strategy_name);
    if (it == m_strategies.cend()) {
        return *(m_strategies.at("Default"));
    }
    return *(it->second);
}

}
