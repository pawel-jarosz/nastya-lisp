set(LISP_EXPRESSION_LIBRARY_SRC
        Interface/IObject.hpp
        Interface/IObjectStorage.hpp
        Interface/IObjectFactory.hpp
        Interface/IExpressionBuilder.hpp
        TypeSystem/ObjectType.hpp
        TypeSystem/GenericObject.hpp
        TypeSystem/ListObject.hpp
        TypeSystem/BooleanObject.hpp
        TypeSystem/LabelObject.hpp
        TypeSystem/NumberObject.hpp
        TypeSystem/StringObject.hpp
        TypeSystem/TypeSystemImpl.cpp
        Testing/ListBuilder.hpp
        Testing/ListBuilder.cpp
        LispExpressionBuilder.hpp
        LispExpressionBuilder.cpp
        ObjectStorage.hpp
        ObjectStorage.cpp
        ObjectFactory.hpp
        ObjectFactory.cpp
        ObjectFactoryBuilder.hpp
        ObjectFactoryBuilder.cpp
)

add_library(LispExpression SHARED ${LISP_EXPRESSION_LIBRARY_SRC})
set_target_properties(LispExpression PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(LispExpression Parser ${BUT_LIBRARIES})
target_include_directories(LispExpression PRIVATE ${BUT_INCLUDE_DIRS})

add_executable(LispExpressionTest TypeSystem/TypeSystemImplTest.cpp
        ObjectStorageTest.cpp
        ObjectFactoryTest.cpp
        ObjectFactoryBuilderTest.cpp
)

target_link_libraries(LispExpressionTest ${TESTING_FRAMEWORK} LispExpression)

add_test(NAME LispExpressionLibraryTest COMMAND LispExpressionTest)
