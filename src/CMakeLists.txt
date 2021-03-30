set (NEUN_INCLUDE_DIRS ../thirdparty/Neun/include ../thirdparty/Neun/concepts ../thirdparty/Neun/models ../thirdparty/Neun/integrators ../thirdparty/Neun/wrappers ../thirdparty/Neun/archetypes)
set (STATS_INCLUDE_DIRS ../thirdparty/libStats)
include_directories(../include ${NEUN_INCLUDE_DIRS} ${YAMLCPP_INCLUDE_DIR} ${STATS_INCLUDE_DIRS} ${HDF5_INCLUDE_DIRS} ../thirdparty/GA)

set ( EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/bin)

add_executable(emmodel emmodel.cpp)
target_link_libraries(emmodel ${YAMLCPP_LIBRARY})

install(TARGETS emmodel
    RUNTIME DESTINATION "/usr/bin"
    LIBRARY DESTINATION "/usr/lib"
    PUBLIC_HEADER DESTINATION "/usr/include"
    DESTINATION "/usr/share"
)

link_libraries("-static")
add_executable(emmodelGAFit emmodelGAFit.cpp)
add_dependencies(emmodelGAFit GA)
set_target_properties(emmodelGAFit PROPERTIES LINK_FLAGS "-static" )
target_link_libraries(emmodelGAFit ${YAMLCPP_LIBRARY} ${CMAKE_SOURCE_DIR}/thirdparty/GA/ga/libga.a)

install(TARGETS emmodelGAFit
    RUNTIME DESTINATION "/usr/bin"
    LIBRARY DESTINATION "/usr/lib"
    PUBLIC_HEADER DESTINATION "/usr/include"
    DESTINATION "/usr/share"
)