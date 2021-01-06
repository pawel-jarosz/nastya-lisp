set(CLI_SOURCE
        ConsoleManager.hpp
        ConsoleManager.cpp
        Interface/IConsoleManager.hpp
        Interface/IInputSource.hpp
        Interface/IOutputSink.hpp
        Interface/IIoFactory.hpp
        IO/InputStream.hpp
        IO/InputStream.cpp
        IO/OutputStream.hpp
        IO/OutputStream.cpp
        IO/StreamWrapperFactory.hpp
        IO/StreamWrapperFactory.cpp
        Module/ConsoleModule.hpp
        Module/ConsoleModule.cpp
        Module/ConsoleEvaluators.hpp
        Module/ConsoleEvaluators.cpp
        Module/ConsoleModuleBuilder.hpp
        Module/ConsoleModuleBuilder.cpp
)

add_library(Cli ${CLI_SOURCE})
target_link_libraries(Cli Builtins Modules LispExpression Parser VM)

add_executable(nastya-cli main.cpp)
target_link_libraries(nastya-cli Cli)
