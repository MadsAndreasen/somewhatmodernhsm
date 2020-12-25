cmake_policy(SET CMP0048 NEW)

project("Modern HSM" VERSION 1.0.0)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

set(DO_LINT OFF)

if(${DO_LINT})
    set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=*,-fuchsia-*)
endif()


add_subdirectory(src)
add_subdirectory(example)

enable_testing()
add_subdirectory(tests)
