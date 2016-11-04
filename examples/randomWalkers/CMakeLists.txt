
find_package(Boost COMPONENTS filesystem system date_time timer chrono REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(TinyXML REQUIRED)
include_directories(${TinyXML_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(PythonInterp 2.7 REQUIRED)

set(generateMPI ${CMAKE_SOURCE_DIR}/bin/generateMpi.py)

set(mpiAgentsSrc mpiCode/FactoryCode.cxx mpiCode/RandomAgent_mpi.cxx)
set(mpiAgentsSrcFullPath ${CMAKE_CURRENT_SOURCE_DIR}/mpiCode/FactoryCode.cxx ${CMAKE_CURRENT_SOURCE_DIR}/mpiCode/RandomAgent_mpi.cxx)
set(AgentsSrc 'main.cxx' 'RandomAgent.cxx')
set(AgentsEnv '{"namespaces":["Examples"]}')

MESSAGE( STATUS "AgentsEnv:         " ${AgentsEnv} )
MESSAGE( STATUS "AgentsSrc:         " ${mpiAgentsSrc} )

add_custom_command(
  OUTPUT ${mpiAgentsSrcFullPath}
  COMMAND ${PYTHON_EXECUTABLE} ${generateMPI} --target ${mpiAgentsSrc} --source ${AgentsSrc} --env ${AgentsEnv}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR/mpiCode})

file(GLOB SOURCES "*.cxx")

add_executable(randomWalk ${SOURCES} ${mpiAgentsSrcFullPath})
target_link_libraries(randomWalk pandora ${Boost_LIBRARIES} ${TinyXML_LIBRARIES})
install(TARGETS randomWalk DESTINATION /usr/lib)
