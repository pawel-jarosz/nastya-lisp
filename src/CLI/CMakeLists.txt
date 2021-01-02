set(CLI_SOURCE
        main.cpp
        ConsoleManager.hpp
        ConsoleManager.cpp
        Interface/IConsoleManager.hpp
        Module/ConsoleModule.hpp
        Module/ConsoleModule.cpp
        Module/ConsoleEvaluators.hpp
        Module/ConsoleEvaluators.cpp
        Module/ConsoleModuleBuilder.hpp
        Module/ConsoleModuleBuilder.cpp
)
add_executable(nastya-cli ${CLI_SOURCE})
target_link_libraries(nastya-cli Builtins Modules LispExpression Parser VM)