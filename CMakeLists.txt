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

# Load global install rules
include(${CMAKE_COMMON_CMAKE_DIR}/InstallRules.cmake)
# Load external libs
include(${CMAKE_COMMON_CMAKE_DIR}/CommonLibs.cmake)

add_subdirectory(src)
add_subdirectory(examples/randomWalkers)
add_subdirectory(examples/epidemy)
add_subdirectory(cassandra)


# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/include")

get_property(ALL_INCLUDE_DIRS DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
configure_package_config_file(
  "${CMAKE_SOURCE_DIR}/CMake/PandoraConfig.cmake.in"
  "${CMAKE_BINARY_DIR}/PandoraConfig.cmake"  
   INSTALL_DESTINATION "${INSTALL_CMAKE_DIR}"
   PATH_VARS ALL_INCLUDE_DIRS )


# ... for the install tree
set(CONF_INCLUDE_DIRS "${PANDORA_CMAKE_DIR}/${INCLUDE_DIR}")
configure_file(${CMAKE_SOURCE_DIR}/CMake/PandoraConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/PandoraConfig.cmake" @ONLY)
# ... for both
configure_file(${CMAKE_SOURCE_DIR}/CMake/PandoraConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/PandoraConfigVersion.cmake" @ONLY)
 
# Install the PandoraConfig.cmake and PandoraConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/PandoraConfig.cmake"
  "${PROJECT_BINARY_DIR}/PandoraConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)


# Add all targets to the build-tree export set
export(TARGETS pandora pyPandora randomWalk epidemy 
  FILE "${PROJECT_BINARY_DIR}/PandoraTargets.cmake")



