cmake_minimum_required(VERSION 3.10)

# Set the project name
project(04_shaders)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
add_executable(04_shaders main.cpp ShaderProgram.cpp)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

# Find GLEW
find_package(GLEW REQUIRED)

# Include directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) 

# Link libraries
target_link_libraries(04_shaders
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
)

