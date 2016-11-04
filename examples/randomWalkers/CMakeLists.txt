
find_package(Boost COMPONENTS filesystem system date_time timer chrono REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(TinyXML REQUIRED)
include_directories(${TinyXML_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(PythonInterp 2.7 REQUIRED)

set(generateMPI ${CMAKE_SOURCE_DIR}/bin/generateMpi.py)

set(mpiAgentsSrc 'mpiCode/FactoryCode.cxx' 'mpiCode/RandomAgent_mpi.cxx')
set(AgentsSrc 'main.cxx' 'RandomAgent.cxx')
set(AgentsEnv '{"namespaces":"Example"}')

MESSAGE( STATUS "AgentsEnv:         " ${AgentsEnv} )
MESSAGE( STATUS "AgentsSrc:         " ${mpiAgentsSrc} )

add_custom_command(
  OUTPUT ${mpiAgentsSrc}
  COMMAND ${PYTHON_EXECUTABLE} ${generateMPI} --target ${mpiAgentsSrc} --source ${AgentsSrc} --env ${AgentsEnv}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SOURCES "*.cxx")
file(GLOB SOURCES_MPI RELATIVE "mpiCode" "*.cxx")

add_executable(randomWalk ${SOURCES_MPI})
target_link_libraries(randomWalk pandora ${Boost_LIBRARIES} ${TinyXML_LIBRARIES})
install(TARGETS randomWalk DESTINATION /usr/lib)
