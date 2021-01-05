set(CLI_SOURCE
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

add_library(Cli ${CLI_SOURCE})
add_executable(nastya-cli main.cpp)
target_link_libraries(nastya-cli Cli Builtins Modules LispExpression Parser VM)