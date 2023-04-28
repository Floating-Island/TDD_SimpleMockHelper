cmake_minimum_required(VERSION 3.21)

# set the project name and version
project(simplemockhelperplugin${CMAKE_SYSTEM_NAME} VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# enable testing that's needed for the test_SimpleMockHelper.cpp file in CTest
include(CTest)
enable_testing()

# add source subdirectory
add_subdirectory(source)
