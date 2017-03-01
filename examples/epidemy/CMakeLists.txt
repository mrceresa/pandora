
find_package(Boost COMPONENTS filesystem system date_time timer chrono REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(TinyXML REQUIRED)
include_directories(${TinyXML_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(PythonInterp 2.7 REQUIRED)

set(generateMPI ${CMAKE_SOURCE_DIR}/bin/generateMpi.py)

set(mpiAgentsSrc mpiCode/FactoryCode.cxx mpiCode/Human_mpi.cxx)
set(mpiAgentsSrcFullPath ${CMAKE_CURRENT_SOURCE_DIR}/mpiCode/FactoryCode.cxx ${CMAKE_CURRENT_SOURCE_DIR}/mpiCode/Human_mpi.cxx)
set(AgentsSrc 'main.cxx' 'Human.cxx')
set(AgentsEnv '{"namespaces":["Examples"]}')

MESSAGE( STATUS "AgentsEnv:         " ${AgentsEnv} )
MESSAGE( STATUS "AgentsSrc:         " ${mpiAgentsSrc} )

add_custom_command(
  OUTPUT ${mpiAgentsSrcFullPath}
  COMMAND ${PYTHON_EXECUTABLE} ${generateMPI} --target ${mpiAgentsSrc} --source ${AgentsSrc} --env ${AgentsEnv}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mpiCode)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mpiCode)

file(GLOB SOURCES "*.cxx")
file(COPY config.xml DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(epidemy ${SOURCES} ${mpiAgentsSrcFullPath})
target_link_libraries(epidemy pandora ${Boost_LIBRARIES} ${TinyXML_LIBRARIES})
#install(TARGETS epidemy DESTINATION /usr/local/bin)
