add_executable(nastya-cli main.cpp ConsoleManager.hpp ConsoleManager.cpp)
target_link_libraries(nastya-cli Builtins Modules LispExpression Parser VM)