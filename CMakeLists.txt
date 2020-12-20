project("Modern HSM")
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(example)

enable_testing()
add_subdirectory(tests)
