set(BUILTINS_LIBRARY_SRC
        Arithmetic/ArithmeticEvaluators.hpp
        Arithmetic/ArithmeticEvaluators.cpp
        Arithmetic/ArithmeticModule.hpp
        Arithmetic/ArithmeticModule.cpp
        Lists/ListsEvaluators.hpp
        Lists/ListsEvaluators.cpp
        Lists/ListsModule.hpp
        Lists/ListsModule.cpp
        Compare/CompareEvaluators.hpp
        Compare/CompareEvaluators.cpp
        Compare/CompareModule.hpp
        Compare/CompareModule.cpp
        Syntax/SyntaxEvaluators.hpp
        Syntax/SyntaxEvaluators.cpp
        Syntax/SyntaxModule.hpp
        Syntax/SyntaxModule.cpp
        BuiltinsModuleBuilder.hpp
        BuiltinsModuleBuilder.cpp)

add_library(Builtins SHARED ${BUILTINS_LIBRARY_SRC})
set_target_properties(Builtins PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Builtins Modules Utilities Runtime LispExpression)

