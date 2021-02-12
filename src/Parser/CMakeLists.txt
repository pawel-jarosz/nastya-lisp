set(PARSER_LIBRARY_SRC
    Types/Token.hpp
    TokenImpl.cpp
        Tokenizer.hpp
        Tokenizer.cpp
    ParserException.hpp
    SimpleTokenizers/AtomValidator.hpp
    SimpleTokenizers/AtomValidator.cpp
    SimpleTokenizers/BooleanValidator.hpp
    SimpleTokenizers/BooleanValidator.cpp
    SimpleTokenizers/CompositeValidator.hpp
    SimpleTokenizers/CompositeValidator.cpp
    SimpleTokenizers/LabelValidator.hpp
    SimpleTokenizers/LabelValidator.cpp
    SimpleTokenizers/NumberValidator.hpp
    SimpleTokenizers/NumberValidator.cpp
    SimpleTokenizers/StringValidator.hpp
    SimpleTokenizers/StringValidator.cpp
    SimpleTokenizers/ReservedCharacterValidator.hpp
    SimpleTokenizers/ReservedCharacterValidator.cpp
    SimpleTokenizers/OmitBlanksValidator.hpp
    SimpleTokenizers/OmitBlanksValidator.cpp)

add_library(Parser SHARED ${PARSER_LIBRARY_SRC})
set_target_properties(Parser PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Parser PRIVATE ${BUT_INCLUDE_DIRS})
target_link_libraries(Parser PRIVATE ${BUT_LIBRARIES})
