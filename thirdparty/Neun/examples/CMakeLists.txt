set (INCLUDE_DIR ../include)
include_directories(${INCLUDE_DIR} ../concepts ../models ../integrators ../wrappers ../archetypes)

add_executable(izk_neuron izk_neuron.cpp)
target_link_libraries(izk_neuron) 