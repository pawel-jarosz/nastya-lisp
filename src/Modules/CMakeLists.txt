set(MODULES_LIBRARY_SRC
        Interface/IModule.hpp
        Interface/IModuleRegistry.hpp
        Module.hpp
        Module.cpp
        ModuleRegistry.hpp
        ModuleRegistry.cpp
        ModuleBuilder.hpp)

add_library(Modules SHARED ${MODULES_LIBRARY_SRC})
set_target_properties(Modules PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(Modules TypeSystem)

