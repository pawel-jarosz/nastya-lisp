set(PARSER_LIBRARY_SRC
    Types/Token.hpp
    TokenImpl.cpp)

add_library(Parser SHARED ${PARSER_LIBRARY_SRC})
set_target_properties(Parser PROPERTIES LINKER_LANGUAGE CXX)
