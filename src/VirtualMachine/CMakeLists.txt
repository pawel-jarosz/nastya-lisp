set(VM_LIBRARY_SRC
        Interface/IArgumentPreparationStrategy.hpp
        Interface/IArgumentPreparationManager.hpp
        ArgumentPreparationStrategy/DefaultStrategy.hpp
        ArgumentPreparationStrategy/DefineStrategy.hpp
        ArgumentPreparationStrategy/LetInStrategy.hpp
        ArgumentPreparationStrategy/QuoteStrategy.hpp
        ArgumentPreparationStrategy/CondStrategy.hpp
        ArgumentPreparationStrategy/ArgumentPreparationStrategies.cpp
        Machine.hpp
        Machine.cpp
        ArgumentPreparationManager.hpp
        ArgumentPreparationManager.cpp
        MachineRuntimeException.hpp)

add_library(VM SHARED ${VM_LIBRARY_SRC})
set_target_properties(VM PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(VM Modules Utilities LispExpression Modules)
