//
// Created by caedus on 20.12.2020.
//

#pragma once

#include "Modules/Interface/IModule.hpp"

namespace nastya::modules {

class AbstractModule : public IModule {
public:
    explicit AbstractModule(std::string module_name);
    std::string getModuleName() const override;
private:
    std::string m_module_name;
};

}
