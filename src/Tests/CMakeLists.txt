add_executable(Tests LispExpressionBuilderTest.cpp ExecutorEnvironmentTest.cpp)

target_link_libraries(Tests ${TESTING_FRAMEWORK} Builtins Modules LispExpression Parser VM)

add_test(NAME IntegrationTests COMMAND Tests)
