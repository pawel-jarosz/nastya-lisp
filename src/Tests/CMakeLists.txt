add_executable(Tests LispExpressionBuilderTest.cpp ExecutorEnvironmentTest.cpp)

find_package(GTest REQUIRED)

target_link_libraries(Tests GTest::gtest GTest::gmock GTest::gtest_main Builtins Modules LispExpression Parser VM)

add_test(NAME IntegrationTests COMMAND Tests)
