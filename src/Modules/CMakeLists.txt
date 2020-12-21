set(MODULES_LIBRARY_SRC
        Interface/IModule.hpp
        AbstractModule.hpp
        AbstractModule.cpp
        ModuleRegistry.hpp
        ModuleRegistry.cpp)

add_library(Modules SHARED ${MODULES_LIBRARY_SRC})
set_target_properties(Modules PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Modules LispExpression)

add_executable(ModulesTest ModuleRegistryTest.cpp)
find_package(GTest CONFIG REQUIRED)
target_link_libraries(ModulesTest GTest::gtest GTest::gmock GTest::gtest_main Modules)

add_test(NAME ModulesLibraryTest COMMAND ModulesTest)
