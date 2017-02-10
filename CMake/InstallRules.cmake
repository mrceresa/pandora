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



# -- eof
