set(PARSER_LIBRARY_SRC
    Types/Token.hpp
    TokenImpl.cpp
        Tokenizer.hpp
        Tokenizer.cpp
    ParserException.hpp
        TokenProviders/AtomicValueTokenProvider.hpp
        TokenProviders/AtomicValueTokenProvider.cpp
        TokenProviders/BooleanTokenProvider.hpp
        TokenProviders/BooleanTokenProvider.cpp
        TokenProviders/TokenProvidersAggregator.hpp
        TokenProviders/TokenProvidersAggregator.cpp
        TokenProviders/LabelTokenProvider.hpp
        TokenProviders/LabelTokenProvider.cpp
        TokenProviders/NumberTokenProvider.hpp
        TokenProviders/NumberTokenProvider.cpp
        TokenProviders/StringTokenProvider.hpp
        TokenProviders/StringTokenProvider.cpp
        TokenProviders/ReservedCharacterTokenProvider.hpp
        TokenProviders/ReservedCharacterTokenProvider.cpp
        TokenProviders/OmitBlanks.hpp
        TokenProviders/OmitBlanks.cpp)

add_library(Parser SHARED ${PARSER_LIBRARY_SRC})
set_target_properties(Parser PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(Parser PRIVATE ${BUT_INCLUDE_DIRS})
target_link_libraries(Parser PRIVATE ${BUT_LIBRARIES})
