cmake_minimum_required(VERSION 3.0)

set(PROJ rc2)
project(${PROJ} VERSION 0.1)
set(CMAKE_CXX_FLAGS "-Wall -Wextra" CACHE STRING "" FORCE)
set(CMAKE_BUILD_TYPE Debug)

cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

file(GLOB SOURCES
	src/*.cpp
)
add_executable(${PROJ} ${SOURCES})
target_link_libraries(${PROJ} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} m)
