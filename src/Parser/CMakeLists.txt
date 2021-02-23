set(PARSER_LIBRARY_SRC
        Interface/IObjectFactory.hpp
        Interface/IParser.hpp
        Internal/ParserImpl.hpp
        Internal/ParserImpl.cpp
        Parser.hpp
        Parser.cpp
        ObjectFactory.hpp
        ObjectFactory.cpp
        ObjectFactoryBuilder.hpp
        ObjectFactoryBuilder.cpp
)

add_library(Parser SHARED ${PARSER_LIBRARY_SRC})
set_target_properties(Parser PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Parser Tokenizer TypeSystem ${BUT_LIBRARIES})
target_include_directories(Parser PRIVATE ${BUT_INCLUDE_DIRS})
