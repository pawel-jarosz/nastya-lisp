set(LISP_EXPRESSION_LIBRARY_SRC
        ../TypeSystem/Interface/IObject.hpp
        ../TypeSystem/Interface/IObjectStorage.hpp
        Interface/IObjectFactory.hpp
        Interface/IExpressionBuilder.hpp
        Testing/ListBuilder.hpp
        Testing/ListBuilder.cpp
        LispExpressionBuilder.hpp
        LispExpressionBuilder.cpp
        ../TypeSystem/ObjectStorage.hpp
        ../TypeSystem/ObjectStorage.cpp
        ObjectFactory.hpp
        ObjectFactory.cpp
        ObjectFactoryBuilder.hpp
        ObjectFactoryBuilder.cpp
)

add_library(LispExpression SHARED ${LISP_EXPRESSION_LIBRARY_SRC})
set_target_properties(LispExpression PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(LispExpression Parser TypeSystem ${BUT_LIBRARIES})
target_include_directories(LispExpression PRIVATE ${BUT_INCLUDE_DIRS})
