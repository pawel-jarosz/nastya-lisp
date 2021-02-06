//
// Created by caedus on 06.02.2021.
//

#include "Builtins/BuiltinsModulesFactory.hpp"

#include "Builtins/Syntax/SyntaxModule.hpp"
#include "Builtins/Compare/CompareModule.hpp"
#include "Builtins/Lists/ListsModule.hpp"
#include "Builtins/Arithmetic/ArithmeticModule.hpp"

namespace nastya::builtins {

std::unique_ptr<modules::IModule> BuiltinsModulesFactory::createSyntax() const
{
    const auto builder = syntax::create_module_builder();
    return builder->build();
}

std::unique_ptr<modules::IModule> BuiltinsModulesFactory::createLists() const
{
    const auto builder = lists::create_module_builder();
    return builder->build();
}

std::unique_ptr<modules::IModule> BuiltinsModulesFactory::createCompare() const
{
    const auto builder = compare::create_module_builder();
    return builder->build();
}

std::unique_ptr<modules::IModule> BuiltinsModulesFactory::createArithmetic() const
{
    const auto builder = arithmetic::create_module_builder();
    return builder->build();
}

}
