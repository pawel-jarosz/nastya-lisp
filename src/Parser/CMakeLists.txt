set(PARSER_LIBRARY_SRC
    Types/Token.hpp
    TokenImpl.cpp
    DummyParser.hpp
    DummyParser.cpp)

add_library(Parser SHARED ${PARSER_LIBRARY_SRC})
set_target_properties(Parser PROPERTIES LINKER_LANGUAGE CXX)

add_executable(ParserTest DummyParserTest.cpp)
find_package(GTest REQUIRED)
target_link_libraries(ParserTest GTest::GTest GTest::Main Parser)

add_test(NAME ParserLibraryTest COMMAND ParserTest)
