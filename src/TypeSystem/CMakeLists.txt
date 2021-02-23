set(TYPESYSTEM_LIBRARY_SRC
        Types/ObjectType.hpp
        Types/GenericObject.hpp
        Types/ComparableTrait.hpp
        Types/LambdaObject.hpp
        Types/ListObject.hpp
        Types/BooleanObject.hpp
        Types/LabelObject.hpp
        Types/NumberObject.hpp
        Types/StringObject.hpp
        Internal/GenericObject.cpp
        Interface/IObject.hpp
        Interface/IObjectStorage.hpp
        ObjectStorage.hpp
        ObjectStorage.cpp
        Internal/StringObject.cpp
        Internal/BooleanObject.cpp
        Internal/NumberObject.cpp
        Internal/LabelObject.cpp
        Internal/ListObject.cpp
        Internal/LambdaObject.cpp)

add_library(TypeSystem SHARED ${TYPESYSTEM_LIBRARY_SRC})
set_target_properties(TypeSystem PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(TypeSystem PRIVATE ${BUT_INCLUDE_DIRS})
