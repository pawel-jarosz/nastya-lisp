add_executable(ModulesTest Modules/ModuleTest.cpp)
target_link_libraries(ModulesTest ${TESTING_FRAMEWORK} Modules Runtime)
add_test(NAME ModulesLibraryTest COMMAND ModulesTest)