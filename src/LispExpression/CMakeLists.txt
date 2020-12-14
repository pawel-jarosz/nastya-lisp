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
