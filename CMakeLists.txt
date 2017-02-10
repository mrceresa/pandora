cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")
set(CMAKE_COMMON_CMAKE_DIR ${CMAKE_COMMON_CMAKE_DIR} "${CMAKE_SOURCE_DIR}/CMake")

project(pandora)

# Load global install rules
INCLUDE(${CMAKE_COMMON_CMAKE_DIR}/InstallRules.cmake)
# Load external libs
INCLUDE(${CMAKE_COMMON_CMAKE_DIR}/CommonLibs.cmake)


add_subdirectory(src)
add_subdirectory(examples/randomWalkers)
add_subdirectory(examples/epidemy)



