cmake_minimum_required(VERSION 3.16)
project(nastya_lisp CXX)

set(CMAKE_CXX_STANDARD 17)

include(modules/FindBut.cmake)

if (NOT DEFINED ENABLED_CODE_COVERAGE)
    set(ENABLED_CODE_COVERAGE 0)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (${ENABLED_CODE_COVERAGE})
    include(modules/CodeCoverage.cmake)
    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(
            NAME ctest_coverage                    # New target name
            EXECUTABLE ctest -j ${PROCESSOR_COUNT} # Executable in PROJECT_BINARY_DIR
            EXCLUDE src/Tests src/NewTests/ src/Parser/Testing src/Modules/Testing
            src/Tokenizer/Testing src/VirtualMachine/Testing
                    src/CLI/Testing src/Runtime/Testing src/CLI/main.cpp
    )
endif()

enable_testing()
add_subdirectory(src)
