cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

project(pandora)

find_package(GDAL REQUIRED)

#Bring the headers, such as Student.h into the project
include_directories(include include/analysis)

file(GLOB coreFILES "src/*.cxx")
file(GLOB analysisFILES "src/analysis/*.cxx")

add_library(pandora SHARED ${coreFILES} ${analysisFILES})

set_target_properties(pandora PROPERTIES COMPILE_FLAGS "-fpermissive")

##### MPI ###
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

if(MPI_COMPILE_FLAGS)
  set_target_properties(pandora PROPERTIES
    COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
  set_target_properties(pandora PROPERTIES
    LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()

##### GDAL ###
find_package(GDAL REQUIRED)
include_directories(${GDAL_INCLUDE_DIR})

target_link_libraries(pandora ${MPI_LIBRARIES} ${GDAL_LIBRARY})

install(TARGETS pandora DESTINATION /usr/local/lib64)

add_subdirectory(examples/randomWalkers)
add_subdirectory(examples/epidemy)



