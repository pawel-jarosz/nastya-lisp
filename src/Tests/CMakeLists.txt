add_executable(Tests LispExpressionBuilderTest.cpp)

find_package(GTest REQUIRED CONFIG)

target_link_libraries(Tests GTest::gtest GTest::gmock GTest::gtest_main LispExpression Parser)

add_test(NAME IntegrationTests COMMAND Tests)
