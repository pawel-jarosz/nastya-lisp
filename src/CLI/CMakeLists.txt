set(CLI_SOURCE
        ConsoleManager.hpp
        ConsoleManager.cpp
        PreloadFromFile.hpp
        PreloadFromFile.cpp
        Interface/IConsoleManager.hpp
        Interface/IInputSource.hpp
        Interface/IOutputSink.hpp
        Interface/IIoFactory.hpp
        Interface/ISplashScreen.hpp
        IO/InputStream.hpp
        IO/InputStream.cpp
        IO/OutputStream.hpp
        IO/OutputStream.cpp
        IO/StreamWrapperFactory.hpp
        IO/StreamWrapperFactory.cpp
        SplashScreen/SplashScreen.hpp
        SplashScreen/SplashScreen.cpp
        Module/ConsoleModule.hpp
        Module/ConsoleModule.cpp
        Module/ConsoleEvaluators.hpp
        Module/ConsoleEvaluators.cpp
        Module/ConsoleModuleRegistration.hpp
        Module/ConsoleModuleRegistration.cpp
)

add_library(Cli ${CLI_SOURCE})
target_link_libraries(Cli Builtins Modules Parser Tokenizer VM)

add_executable(nastya-cli main.cpp)
target_link_libraries(nastya-cli Cli)
