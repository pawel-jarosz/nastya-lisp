//
// Created by caedus on 31.12.2020.
//

#include "Builtins/BuiltinsModuleBuilder.hpp"
#include "CLI/ConsoleManager.hpp"
#include "CLI/IO/StreamWrapperFactory.hpp"
#include "LispExpression/LispExpressionBuilder.hpp"
#include "LispExpression/ObjectFactory.hpp"
#include "LispExpression/ObjectFactoryBuilder.hpp"
#include "Module/ConsoleModuleBuilder.hpp"
#include "Modules/ModuleRegistry.hpp"
#include "Parser/DummyParser.hpp"
#include "VirtualMachine/Machine.hpp"
#include "CLI/SplashScreen/SplashScreen.hpp"

#include <iostream>

void initModules(nastya::lisp::ObjectFactory& object_factory, nastya::modules::ModuleRegistry& module_registry)
{
    nastya::lisp::ObjectFactoryBuilder object_factory_builder(object_factory);
    object_factory_builder.build();
    nastya::builtins::BuiltinsModuleBuilder builtins_builder(module_registry);
    builtins_builder.build();
}

nastya::cli::splashscreen::SplashScreen createSplashScreen() {
    std::vector<std::string> message = {
        "\t  __________________________________",
        "\t |                                  |",
        "\t | Nastya Lisp                      |",
        "\t | v. 2021.0.1                      |",
        "\t |__________________________________|\n"
    };
    return nastya::cli::splashscreen::SplashScreen(message);
}

int main(int argc, char* argv[])
{
    nastya::lisp::ObjectFactory object_factory;
    nastya::modules::ModuleRegistry module_registry;
    auto splashscreen = createSplashScreen();
    initModules(object_factory, module_registry);
    nastya::parser::DummyParser parser;
    nastya::lisp::LispExpressionBuilder expressionBuilder(parser, object_factory);
    nastya::vm::Machine machine(module_registry);
    nastya::cli::io::stdio::StreamWrapperFactory io_factory(std::cin, std::cout);
    nastya::cli::ConsoleManager console_manager(machine, parser, expressionBuilder, io_factory, splashscreen);
    nastya::cli::module::ConsoleModuleBuilder consoleModuleBuilder(module_registry, console_manager);
    consoleModuleBuilder.build();
    console_manager.splashScreen();
    auto return_code = console_manager.run();
    return return_code;
}