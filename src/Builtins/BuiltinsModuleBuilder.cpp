//
// Created by caedus on 21.12.2020.
//

#include "Builtins/BuiltinsModuleBuilder.hpp"
#include "Builtins/Lists/ListsModule.hpp"
#include "Builtins/Compare/CompareModule.hpp"
#include "Builtins/Syntax/SyntaxModule.hpp"
#include "Builtins/Arithmetic/ArithmeticModule.hpp"

namespace nastya::builtins {

BuiltinsModuleBuilder::BuiltinsModuleBuilder(modules::ModuleRegistry& registry) : m_registry{registry}
{
}

void BuiltinsModuleBuilder::build() const
{
    m_registry
        .registerModule(lists::ListsModule::getInstance())
        .registerModule(compare::CompareModule::getInstance())
        .registerModule(syntax::SyntaxModule::getInstance())
        .registerModule(arithmetic::ArithmeticModule::getInstance());
}

}  // namespace nastya::builtins