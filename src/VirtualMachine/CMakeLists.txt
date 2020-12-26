set(VM_LIBRARY_SRC
        Machine.hpp
        Machine.cpp)

add_library(VM SHARED ${VM_LIBRARY_SRC})
set_target_properties(VM PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(VM Modules LispExpression Modules)
