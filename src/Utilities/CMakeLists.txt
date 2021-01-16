set(UTILITIES_SRC LispCast.hpp LispCast.cpp)
add_library(Utilities SHARED ${UTILITIES_SRC})
target_link_libraries(Utilities LispExpression)