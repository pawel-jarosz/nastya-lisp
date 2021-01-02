//
// Created by caedus on 31.12.2020.
//

#include "Parser/DummyParser.hpp"
#include "LispExpression/ObjectFactoryBuilder.hpp"
#include "LispExpression/ObjectFactory.hpp"
#include "VirtualMachine/Machine.hpp"
#include "Modules/ModuleRegistry.hpp"
#include "Builtins/BuiltinsModuleBuilder.hpp"
#include "LispExpression/LispExpressionBuilder.hpp"
#include "Module/ConsoleModuleBuilder.hpp"

#include "ConsoleManager.hpp"

void initModules(nastya::lisp::ObjectFactory& object_factory, nastya::modules::ModuleRegistry& module_registry) {
    nastya::lisp::ObjectFactoryBuilder object_factory_builder(object_factory);
    object_factory_builder.build();
    nastya::builtins::BuiltinsModuleBuilder builtins_builder(module_registry);
    builtins_builder.build();
}

int main(int argc, char* argv[]) {
    nastya::lisp::ObjectFactory object_factory;
    nastya::modules::ModuleRegistry module_registry;
    initModules(object_factory, module_registry);
    nastya::parser::DummyParser parser;
    nastya::lisp::LispExpressionBuilder expressionBuilder(parser, object_factory);
    nastya::vm::Machine machine(module_registry);
    nastya::cli::ConsoleManager console_manager(machine, parser, expressionBuilder);
    nastya::cli::module::ConsoleModuleBuilder consoleModuleBuilder(module_registry, console_manager);
    consoleModuleBuilder.build();
    console_manager.splashScreen();
    auto return_code = console_manager.run();
    return return_code;
}