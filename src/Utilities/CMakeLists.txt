set(UTILITIES_SRC LispCast.hpp LispCast.cpp ListBuilder.hpp ListBuilder.cpp)
add_library(Utilities SHARED ${UTILITIES_SRC})
target_link_libraries(Utilities TypeSystem)