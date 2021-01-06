add_executable(ModulesTest ModuleTest.cpp ModuleRegistryTest.cpp)
target_link_libraries(ModulesTest ${TESTING_FRAMEWORK} Modules)
add_test(NAME ModulesLibraryTest COMMAND ModulesTest)

add_executable(Tests LispExpressionBuilderTest.cpp ExecutorEnvironmentTest.cpp)
target_link_libraries(Tests ${TESTING_FRAMEWORK} Builtins Modules LispExpression Parser VM)
add_test(NAME IntegrationTests COMMAND Tests)

add_executable(BuiltinsTest BuiltinsModuleBuilderTest.cpp ListsModuleTest.cpp)
target_link_libraries(BuiltinsTest ${TESTING_FRAMEWORK} Builtins)
add_test(NAME BuiltinsLibraryTest COMMAND BuiltinsTest)

add_executable(LispExpressionTest TypeSystemImplTest.cpp
        ObjectStorageTest.cpp
        ObjectFactoryTest.cpp
        ObjectFactoryBuilderTest.cpp
        )
target_link_libraries(LispExpressionTest ${TESTING_FRAMEWORK} LispExpression)
add_test(NAME LispExpressionLibraryTest COMMAND LispExpressionTest)

add_executable(ParserTest DummyParserTest.cpp)
target_link_libraries(ParserTest ${TESTING_FRAMEWORK} Parser)
add_test(NAME ParserLibraryTest COMMAND ParserTest)

add_executable(AbstractMachineTest AbstractMachineTest.cpp)
target_link_libraries(AbstractMachineTest ${TESTING_FRAMEWORK} VM)
add_test(NAME AbstractMachineLibraryTest COMMAND AbstractMachineTest)

add_executable(CliTest ConsoleModuleTest.cpp IoStreamTest.cpp)
target_link_libraries(CliTest ${TESTING_FRAMEWORK} Cli Modules LispExpression)
add_test(NAME CliLibraryTest COMMAND CliTest)
