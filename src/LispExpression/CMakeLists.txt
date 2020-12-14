set(LISP_EXPRESSION_LIBRARY_SRC
        Interface/IObject.hpp
        TypeSystem/ObjectType.hpp
)

add_library(LispExpression SHARED ${LISP_EXPRESSION_LIBRARY_SRC})
set_target_properties(LispExpression PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(LispExpression Parser)
