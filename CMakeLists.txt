cmake_minimum_required(VERSION 3.15)
project(activeObject)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.cpp src/ActiveObject.cpp)
