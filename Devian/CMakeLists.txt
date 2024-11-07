cmake_minimum_required(VERSION 3.1)

# Project name
project(DevianEngine VERSION 0.0.1)

option(BuildTests "Build the unit tests" ON)
enable_testing()

# Enable c++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# TODO: Complete rest of the build system code.

add_executable(../x64/Debug/Devian src/main.cpp)