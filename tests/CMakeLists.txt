project(googletest-git)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)


add_executable(testgtest testgtest.cpp)
add_test(NAME "testgtest" COMMAND testgtest)
target_link_libraries(testgtest gtest gtest_main)


add_executable(testdoor test_door.cpp ../example/door.cpp)
target_include_directories(testdoor PUBLIC ../example)
add_test(NAME "testdoor" COMMAND testdoor)
target_link_libraries(testdoor hsm gtest gtest_main)
