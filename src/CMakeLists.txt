include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Parser)
add_subdirectory(LispExpression)
add_subdirectory(Modules)
add_subdirectory(Builtins)
add_subdirectory(VirtualMachine)
add_subdirectory(Tests)
add_subdirectory(CLI)