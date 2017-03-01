######################### Common libraries
#Bring the headers, such as Student.h into the project
include_directories(include include/analysis)

##### Python #
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
link_directories(${PYTHON_LIBRARIES})
message(STATUS "Found python headers " ${PYTHON_INCLUDE_DIRS})
message(STATUS "Found python libs " ${PYTHON_LIBRARIES})
set(version ${PYTHONLIBS_VERSION_STRING})
STRING( REGEX MATCH "[0-9]"  boost_py_version ${version} )

execute_process(COMMAND python-config --libs OUTPUT_VARIABLE FOO)
message(STATUS "python config is: " ${FOO})
   
############

# Boost stuff
SET(Boost_USE_MULTITHREADED ON)
FIND_PACKAGE(Boost COMPONENTS timer system filesystem chrono program_options date_time python${boost_py_version} REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

##### MPI ###
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
message(STATUS "MPI compile flags " ${MPI_COMPILE_FLAGS})
message(STATUS "MPI link flags " ${MPI_LINK_FLAGS})

##### GDAL ###
find_package(GDAL REQUIRED)
include_directories(${GDAL_INCLUDE_DIR})

#### TinyXML #
find_package(TinyXML REQUIRED)
include_directories(${TinyXML_INCLUDE_DIRS})


##### HDF5 ###
#set(HDF5_PREFER_PARALLEL TRUE)
#find_package(HDF5 COMPONENTS C REQUIRED)
#include_directories(${HDF5_INCLUDE_DIRS})
#message(STATUS ${HDF5_INCLUDE_DIRS})

#set(HDF5_INCLUDE_DIRS "/usr/local/HDF_Group/HDF5/1.8.17/include/")
#set(HDF5_LIBRARIES "/usr/local/HDF_Group/HDF5/1.8.17/lib/libhdf5.a") 
#include_directories(${HDF5_INCLUDE_DIRS})

include_directories("/usr/include/openmpi-x86_64/")

# end Common libraries ####################
