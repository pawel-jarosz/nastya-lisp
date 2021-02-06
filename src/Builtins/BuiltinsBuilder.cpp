//
// Created by caedus on 21.12.2020.
//

#include "Builtins/Arithmetic/ArithmeticModule.hpp"
#include "Builtins/BuiltinsBuilder.hpp"
#include "Builtins/Compare/CompareModule.hpp"
#include "Builtins/Lists/ListsModule.hpp"
#include "Builtins/Syntax/SyntaxModule.hpp"

namespace nastya::builtins {

BuiltinsBuilder::BuiltinsBuilder(modules::ModuleRegistry& registry, IBuiltinsModuleFactory& factory)
: m_registry{registry}
, m_factory{factory}
{
}

void BuiltinsBuilder::build() const
{
    m_registry
        .registerModule(m_factory.createSyntax())
        .registerModule(m_factory.createLists())
        .registerModule(m_factory.createCompare())
        .registerModule(m_factory.createArithmetic());
}

}  // namespace naIstya::builtins