cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")
set(CMAKE_COMMON_CMAKE_DIR ${CMAKE_COMMON_CMAKE_DIR} "${CMAKE_SOURCE_DIR}/CMake")

project(pandora)

set(PANDORA_MAJOR_VERSION 0)
set(PANDORA_MINOR_VERSION 1)
set(PANDORA_PATCH_VERSION 0)
set(PANDORA_VERSION
  ${PANDORA_MAJOR_VERSION}.${PANDORA_MINOR_VERSION}.${PANDORA_PATCH_VERSION})

include( CMakePackageConfigHelpers )

# Load external libs
include(${CMAKE_COMMON_CMAKE_DIR}/CommonLibs.cmake)

add_subdirectory(src)
add_subdirectory(examples/randomWalkers)
add_subdirectory(examples/epidemy)
add_subdirectory(examples/policy)

# Load global install rules
include(${CMAKE_COMMON_CMAKE_DIR}/InstallRules.cmake)

# Add all targets to the build-tree export set
export(TARGETS pandora pyPandora randomWalk epidemy 
  FILE "${PROJECT_BINARY_DIR}/PandoraTargets.cmake")



