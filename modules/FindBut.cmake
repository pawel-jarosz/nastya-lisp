find_library(BUT_LIBRARY NAMES libbut.a
        PATHS
        /usr/lib/
        /usr/local/lib/)
find_path(BUT_INCLUDE_DIR
        But/Optional.hpp)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(But DEFAULT_MSG
        BUT_LIBRARY BUT_INCLUDE_DIR)

if(But_FOUND)
    mark_as_advanced(BUT_LIBRARY BUT_INCLUDE_DIR)
    set(BUT_LIBRARIES    ${BUT_LIBRARY})
    set(BUT_INCLUDE_DIRS ${BUT_INCLUDE_DIR})
endif()
