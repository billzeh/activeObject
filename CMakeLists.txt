cmake_minimum_required(VERSION 3.15)
project(activeObject)

set(CMAKE_CXX_STANDARD 20)
cmake_policy(SET CMP0135 NEW)

include(FetchContent)
FetchContent_Declare(
    googletest
    # Specify the commit you depend on and update it regularly.
    URL https://github.com/google/googletest/archive/v1.15.2.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)
add_library(${PROJECT_NAME} src/ActiveObject.cpp)

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(unitTests
    test/TestActiveObject.cpp)
target_link_libraries(unitTests ${PROJECT_NAME} gtest gtest_main gmock_main)
