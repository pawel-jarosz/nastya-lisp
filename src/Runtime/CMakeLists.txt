set(RUNTIME_LIBRARY_SRC
        Interface/IEvaluator.hpp
        Interface/IMemory.hpp
        Interface/IRuntimeEnvironment.hpp
        Interface/IMachine.hpp
        GenericEvaluator.hpp
        GenericEvaluator.cpp)

add_library(Runtime SHARED ${RUNTIME_LIBRARY_SRC})
set_target_properties(Runtime PROPERTIES LINKER_LANGUAGE CXX)
