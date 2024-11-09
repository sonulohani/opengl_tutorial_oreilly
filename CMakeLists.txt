# Specify minimum version requirement for CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and language (C++)
project(opengl) 

# Optionally, specify different build configurations like Debug or Release:
set(CMAKE_BUILD_TYPE Release) # Or use 'Debug' for debugging builds

# Define the target executable (if you are creating an application):
add_executable(opengl main.cpp)
