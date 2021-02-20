add_executable(ModulesTest Modules/ModuleTest.cpp Modules/ModuleRegistryTest.cpp Modules/ModuleBuilderTest.cpp)
target_link_libraries(ModulesTest ${TESTING_FRAMEWORK} Modules Runtime)
add_test(NAME ModulesLibraryTest COMMAND ModulesTest)

add_executable(TokenizerTest Tokenizer/Common.hpp Tokenizer/Common.cpp
                             Tokenizer/TokenImplTest.cpp
                             Tokenizer/AtomicValueTokenizerTest.cpp
                             Tokenizer/StringValueTokenizerTest.cpp
                             Tokenizer/ReservedCharacterTokenizerTest.cpp
                             Tokenizer/ComplexTokenizerTest.cpp)
target_link_libraries(TokenizerTest ${TESTING_FRAMEWORK} Tokenizer)
add_test(NAME TokenizerLibraryTest COMMAND TokenizerTest)

add_executable(ParserTest Parser/ObjectFactoryTest.cpp)
target_link_libraries(ParserTest ${TESTING_FRAMEWORK} Parser Tokenizer)
add_test(NAME ParserLibraryTest COMMAND ParserTest)
