set(BUILTINS_LIBRARY_SRC
        Lists/ListsEvaluators.hpp
        Lists/ListsEvaluators.cpp
        Lists/ListsModule.hpp
        Lists/ListsModule.cpp
        BuiltinsModuleBuilder.hpp
        BuiltinsModuleBuilder.cpp)

add_library(Builtins SHARED ${BUILTINS_LIBRARY_SRC})
set_target_properties(Builtins PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Builtins Modules LispExpression)

add_executable(BuiltinsTest BuiltinsModuleBuilderTest.cpp Lists/ListsModuleTest.cpp)
target_link_libraries(BuiltinsTest ${TESTING_FRAMEWORK} Builtins)

add_test(NAME BuiltinsLibraryTest COMMAND BuiltinsTest)
