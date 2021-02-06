//
// Created by caedus on 30.01.2021.
//

#pragma once

#include "Modules/Module.hpp"
#include "Runtime/Interface/IEvaluatorFactory.hpp"
#include "Modules/Interface/IModuleBuilder.hpp"

#include <algorithm>

namespace nastya::modules {

template<typename EvaluatorFactory, typename... OtherFactories>
class ModuleBuilder : public ModuleBuilder<OtherFactories...> {
public:
    explicit ModuleBuilder(std::string moduleName);
    std::unique_ptr<IModule> build() override;
};

template<typename EvaluatorFactory>
class ModuleBuilder<EvaluatorFactory> : public IModuleBuilder {
public:
    explicit ModuleBuilder(std::string moduleName);
    std::unique_ptr<IModule> build() override;
    std::vector<std::unique_ptr<runtime::IEvaluatorFactory>>& getFactories() {
        return m_factories;
    }
protected:
    std::unique_ptr<Module> m_module;
    std::string m_module_name;
    std::vector<std::unique_ptr<runtime::IEvaluatorFactory>> m_factories;
};

template<typename EvaluatorFactory, typename... OtherFactory>
std::unique_ptr<IModule> ModuleBuilder<EvaluatorFactory, OtherFactory...>::build() {
    return ModuleBuilder<OtherFactory...>::build();
}

template<typename EvaluatorFactory, typename... OtherFactories>
ModuleBuilder<EvaluatorFactory, OtherFactories...>::ModuleBuilder(std::string moduleName)
    : ModuleBuilder<OtherFactories...>(std::move(moduleName)) {
    std::unique_ptr<runtime::IEvaluatorFactory> factory(new EvaluatorFactory);
    ModuleBuilder<OtherFactories...>::getFactories().emplace_back(std::move(factory));
}

template<typename EvaluatorFactory>
ModuleBuilder<EvaluatorFactory>::ModuleBuilder(std::string moduleName)
: m_module{new Module{moduleName}}
, m_module_name(std::move(moduleName))
, m_factories{}
{
    std::unique_ptr<runtime::IEvaluatorFactory> factory(new EvaluatorFactory);
    m_factories.emplace_back(std::move(factory));
}

template<typename EvaluatorFactory>
std::unique_ptr<IModule> ModuleBuilder<EvaluatorFactory>::build()
{
    using Factory = std::unique_ptr<runtime::IEvaluatorFactory>;
    std::for_each(m_factories.begin(), m_factories.end(), [&](const Factory& factory) {
        m_module->registerFunction(factory->create());
    });
    auto new_module = std::make_unique<Module>(m_module_name);
    m_module.swap(new_module);
    return new_module;
}

}