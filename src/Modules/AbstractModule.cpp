//
// Created by caedus on 20.12.2020.
//

#include "Modules/AbstractModule.hpp"

namespace nastya::modules {

AbstractModule::AbstractModule(std::string module_name) : m_module_name{module_name} {

}

std::string AbstractModule::getModuleName() const {
    return m_module_name;
}

}
