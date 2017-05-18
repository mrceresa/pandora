
### Pandora main lib
file(GLOB coreFILES "*.cxx")
file(GLOB analysisFILES "analysis/*.cxx")
file(GLOB utilsFILES "../utils/*.cxx")
add_library(pandora SHARED ${coreFILES} ${analysisFILES} ${utilsFILES})
set_target_properties(pandora PROPERTIES COMPILE_FLAGS "-fpermissive -fopenmp")

#target_link_libraries(pandora ${MPI_LIBRARIES} ${GDAL_LIBRARY} ${HDF5_LIBRARIES})
target_link_libraries(pandora ${MPI_LIBRARIES} ${GDAL_LIBRARY} ${TinyXML_LIBRARIES})

### Pandora python bindings

file(GLOB pyFILES "pyPandora/*.cxx")

add_library(pyPandora SHARED ${pyFILES} ${coreFILES} ${analysisFILES} ${utilsFILES})
set_target_properties(pyPandora PROPERTIES COMPILE_FLAGS "-fpermissive")

target_link_libraries(pyPandora ${PYTHON_LIBRARIES} ${Boost_LIBRARIES} ${MPI_LIBRARIES}  ${TinyXML_LIBRARIES} ${GDAL_LIBRARY} /usr/lib64/openmpi/lib/libhdf5.so)

#install(FILES pyPandora/pyPandora.py DESTINATION  ${INSTALL_LIB_DIR})
install(TARGETS pandora pyPandora DESTINATION ${INSTALL_LIB_DIR} )
