cmake_minimum_required(VERSION 3.10)

# Set the project name
project(06_virtual_camera)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
add_executable(06_virtual_camera main.cpp ShaderProgram.cpp Texture2D.cpp)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

# Find GLM
pkg_check_modules(GLM REQUIRED glm)

# Find GLEW
find_package(GLEW REQUIRED)

# Include directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

file(COPY airplane.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY crate.jpg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR}) 

# Link libraries
target_link_libraries(06_virtual_camera
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
)

