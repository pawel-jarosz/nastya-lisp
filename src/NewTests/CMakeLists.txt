add_executable(ModulesTest Modules/ModuleTest.cpp Modules/ModuleRegistryTest.cpp)
target_link_libraries(ModulesTest ${TESTING_FRAMEWORK} Modules Runtime)
add_test(NAME ModulesLibraryTest COMMAND ModulesTest)

add_executable(ParserTest Parser/ObjectFactoryTest.cpp)
target_link_libraries(ModulesTest ${TESTING_FRAMEWORK} Modules Runtime)
