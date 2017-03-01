# -- Some CMake definitions

# Headers
#
INSTALL(FILES ${SRC_LIST_ESSENTIAL_H} DESTINATION include)

# Binaries
#

#INSTALL(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib)
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "~/usr/${PROJECT_NAME}" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
endif()

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib64 CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_ARCH_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH  "Installation directory for header files")
MARK_AS_ADVANCED(INSTALL_LIB_DIR INSTALL_BIN_DIR INSTALL_ARCH_DIR INSTALL_INCLUDE_DIR)

set(DEF_INSTALL_CMAKE_DIR lib64/cmake/pandora)

set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

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
 
# Install the FooBarConfig.cmake and FooBarConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/PandoraConfig.cmake"
  "${PROJECT_BINARY_DIR}/PandoraConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)



# -- eof
