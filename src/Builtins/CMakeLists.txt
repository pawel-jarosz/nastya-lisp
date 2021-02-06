set(BUILTINS_LIBRARY_SRC
        Arithmetic/ArithmeticEvaluators.hpp
        Arithmetic/ArithmeticEvaluators.cpp
        Arithmetic/ArithmeticModule.hpp
        Lists/ListsEvaluators.hpp
        Lists/ListsEvaluators.cpp
        Lists/ListsModule.hpp
        Compare/CompareEvaluators.hpp
        Compare/CompareEvaluators.cpp
        Compare/CompareModule.hpp
        Syntax/SyntaxEvaluators.hpp
        Syntax/SyntaxEvaluators.cpp
        Syntax/SyntaxModule.hpp
        BuiltinsBuilder.hpp
        BuiltinsBuilder.cpp
        BuiltinsModulesFactory.hpp
        BuiltinsModulesFactory.cpp
        Interface/IBuiltinsModuleFactory.hpp)

add_library(Builtins SHARED ${BUILTINS_LIBRARY_SRC})
set_target_properties(Builtins PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Builtins Modules Utilities Runtime LispExpression)

