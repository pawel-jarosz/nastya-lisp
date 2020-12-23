add_executable(Tests LispExpressionBuilderTest.cpp ExecutorEnvironmentTest.cpp)

find_package(GTest REQUIRED CONFIG)

target_link_libraries(Tests GTest::gtest GTest::gmock GTest::gtest_main Builtins Modules LispExpression Parser)

add_test(NAME IntegrationTests COMMAND Tests)
