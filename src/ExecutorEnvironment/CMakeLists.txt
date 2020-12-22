set(EXECUTOR_ENVIRONMENT_LIBRARY_SRC
        Machine.hpp
        Machine.cpp)

add_library(ExecutorEnvironment SHARED ${EXECUTOR_ENVIRONMENT_LIBRARY_SRC})
set_target_properties(ExecutorEnvironment PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(ExecutorEnvironment Modules LispExpression)
