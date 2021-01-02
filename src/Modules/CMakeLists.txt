set(MODULES_LIBRARY_SRC
        Interface/IModule.hpp
        Module.hpp
        Module.cpp
        ModuleRegistry.hpp
        ModuleRegistry.cpp)

add_library(Modules SHARED ${MODULES_LIBRARY_SRC})
set_target_properties(Modules PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Modules LispExpression)

find_package(GTest REQUIRED)

add_executable(ModulesTest ModuleTest.cpp ModuleRegistryTest.cpp)
target_link_libraries(ModulesTest GTest::gtest GTest::gmock GTest::gtest_main Modules)

add_test(NAME ModulesLibraryTest COMMAND ModulesTest)
