cmake_minimum_required(VERSION 3.10)

# Set the project name
project(03_index_buffer)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
add_executable(03_index_buffer main.cpp)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

# Find GLEW
find_package(GLEW REQUIRED)

# Include directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

# Link libraries
target_link_libraries(03_index_buffer
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
)

