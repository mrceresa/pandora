
project(cassandra)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB cassandra_sources "*.cxx")
file(GLOB cassandra_includes "*.hxx")
file(GLOB cassandra_uis "uis/*.ui")

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
set (QT_USE_QTOPENGL TRUE)
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )
include_directories(${QT_QTOPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

find_package(Qwt REQUIRED)
include_directories(${QWT_INCLUDE_DIRS})

find_package(DevIL REQUIRED)
include_directories(${IL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

qt4_wrap_ui(UI_HEADERS ${cassandra_uis})
qt4_add_resources(UI_RESOURCES cassandra.qrc)

add_executable(cassandra 
    ${cassandra_sources} 
    ${UI_HEADERS}
    ${UI_RESOURCES})

set_target_properties(cassandra PROPERTIES COMPILE_FLAGS "-fpermissive")

target_link_libraries(cassandra pandora ${QT_LIBRARIES} ${QWT_LIBRARIES} ${IL_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} ${Boost_LIBRARIES} ${TinyXML_LIBRARIES})

install(TARGETS cassandra DESTINATION ${INSTALL_BIN_DIR} )
