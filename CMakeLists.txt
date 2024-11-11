# Specify minimum version requirement for CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and language (C++)
project(opengl) 

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED "glfw3")
pkg_check_modules(GLEW REQUIRED "glew")

include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

# Optionally, specify different build configurations like Debug or Release:
set(CMAKE_BUILD_TYPE Debug) # Or use 'Debug' for debugging builds

# Define the target executable (if you are creating an application):
add_executable(opengl main.cpp)

target_link_libraries(opengl ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})
