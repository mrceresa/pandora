
find_package(Boost COMPONENTS filesystem system date_time timer chrono REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(TinyXML REQUIRED)
include_directories(${TinyXML_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES "*.cxx")

add_executable(randomWalk ${SOURCES})
target_link_libraries(randomWalk pandora ${Boost_LIBRARIES} ${TinyXML_LIBRARIES})
install(TARGETS randomWalk DESTINATION /usr/lib)
