set(LISP_EXPRESSION_LIBRARY_SRC
        Interface/IObject.hpp
        TypeSystem/ObjectType.hpp
        TypeSystem/GenericObject.hpp
        TypeSystem/BooleanObject.hpp
        TypeSystem/LabelObject.hpp
        TypeSystem/NumberObject.hpp
        TypeSystem/StringObject.hpp
        TypeSystem/TypeSystemImpl.cpp
)

add_library(LispExpression SHARED ${LISP_EXPRESSION_LIBRARY_SRC})
set_target_properties(LispExpression PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(LispExpression Parser)

add_executable(LispExpressionTest TypeSystem/TypeSystemImplTest.cpp)

find_package(GTest REQUIRED)
target_link_libraries(LispExpressionTest GTest::GTest GTest::Main LispExpression)

add_test(NAME LispExpressionLibraryTest COMMAND LispExpressionTest)
