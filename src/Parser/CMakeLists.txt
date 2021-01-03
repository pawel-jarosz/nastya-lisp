set(PARSER_LIBRARY_SRC
    Types/Token.hpp
    TokenImpl.cpp
    DummyParser.hpp
    DummyParser.cpp
    ParserException.hpp)

add_library(Parser SHARED ${PARSER_LIBRARY_SRC})
set_target_properties(Parser PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Parser PRIVATE ${BUT_INCLUDE_DIRS})
target_link_libraries(Parser PRIVATE ${BUT_LIBRARIES})

add_executable(ParserTest DummyParserTest.cpp)
target_link_libraries(ParserTest ${TESTING_FRAMEWORK} Parser)

add_test(NAME ParserLibraryTest COMMAND ParserTest)
