set(VM_LIBRARY_SRC
        CallWrapper.hpp
        CallWrapper.cpp
        LambdaCallEvaluator.hpp
        LambdaCallEvaluator.cpp
        Machine.hpp
        Machine.cpp
        MachineRuntimeException.hpp)

add_library(VM SHARED ${VM_LIBRARY_SRC})
set_target_properties(VM PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(VM Modules Utilities LispExpression Modules)
