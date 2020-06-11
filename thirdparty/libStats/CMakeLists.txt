include_directories(. /usr/local/lib ${HDF5_INCLUDE_DIRS})
add_library (libStats STATIC Statistics MatrixStreamer)
target_link_libraries( libStats ${HDF5_LIBRARIES} )

