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

add_executable(ParserTest Parser/ObjectFactoryTest.cpp
                          Parser/ObjectFactoryBuilderTest.cpp
                          Parser/ReductionRulesTest.cpp
                          Parser/ParserTest.cpp)
target_link_libraries(ParserTest ${TESTING_FRAMEWORK} Parser Utilities Tokenizer)
add_test(NAME ParserLibraryTest COMMAND ParserTest)

add_executable(TypeSystemTest TypeSystem/ObjectStorageTest.cpp
                        TypeSystem/BooleanTypeTest.cpp
                        TypeSystem/LabelTypeTest.cpp
                        TypeSystem/StringTypeTest.cpp
                        TypeSystem/ListTypeTest.cpp
                        TypeSystem/NumberTypeTest.cpp
                        TypeSystem/LambdaTypeTest.cpp)
target_link_libraries(TypeSystemTest ${TESTING_FRAMEWORK} Parser Utilities TypeSystem ${BUT_LIBRARY})
add_test(NAME TypeSystemLibraryTest COMMAND TypeSystemTest)

add_executable(BuiltinsTest Builtins/BuiltinsBuilderTest.cpp Builtins/BuiltinsModulesFactoryTest.cpp
                            Builtins/ListsModuleTest.cpp Builtins/CompareModuleTest.cpp Builtins/SyntaxModuleTest.cpp
                            Builtins/ArithmeticModuleTest.cpp)
target_link_libraries(BuiltinsTest ${TESTING_FRAMEWORK} Builtins Modules ${BUT_LIBRARY})
add_test(NAME BuiltinsLibraryTest COMMAND BuiltinsTest)

add_executable(VirtualMachineTest VirtualMachine/CallWrapperTest.cpp)
target_link_libraries(VirtualMachineTest ${TESTING_FRAMEWORK} VM Runtime TypeSystem ${BUT_LIBRARY})
add_test(NAME VirtualMachineLibraryTest COMMAND VirtualMachineTest)
