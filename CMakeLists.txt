cmake_minimum_required(VERSION 3.8)

set(PROJ rc2)
project(${PROJ} VERSION 0.1)
set(CMAKE_CXX_FLAGS "-Wall -Wextra" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS "-Wall -Wextra" CACHE STRING "" FORCE)
set(CMAKE_BUILD_TYPE Debug)

cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(${PROJ} ${SOURCES})
set_property(TARGET ${PROJ} PROPERTY CXX_STANDARD 17)
target_link_libraries(${PROJ} ${OPENGL_LIBRARIES} glfw m)
