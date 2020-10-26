cmake_minimum_required(VERSION 2.8)
project(efish-nmodel CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake.modules/")

# Initialize CXXFLAGS.
set(CMAKE_CXX_FLAGS                "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG          "-Wall -O0 -g -std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG -std=c++14")

#export(PACKAGE Neun)

set(CMake_VERSION_MAJOR "0")
set(CMake_VERSION_MINOR "1")
set(CMake_VERSION_PATCH "0")

set(PROJECT_VERSION ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}.${CMake_VERSION_PATCH})

#include(FindPkgConfig)

FIND_PACKAGE(Boost 1.45 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} include)
	
link_directories(${Boost_LIBRARY_DIRS})

find_package(HDF5 REQUIRED COMPONENTS CXX)
find_package(YamlCpp REQUIRED)

add_custom_target(GA COMMAND make lib
	          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/GA
			   )
add_subdirectory(thirdparty/Neun)
add_subdirectory(thirdparty/libStats)
add_subdirectory(src)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Modeling the variability of the electromotor command system of pulse mormyrids.")
SET(CPACK_PACKAGE_VENDOR "Lareo, A., Varona P. and Rodriguez, FB.")
set(CPACK_PACKAGE_CONTACT "angel.lareo@gmail.com")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "Readme.md")
SET(CPACK_PACKAGE_VERSION_MAJOR ${CMake_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${CMake_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${CMake_VERSION_PATCH})
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")

#SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-program-options1.40.0")
#set(CPACK_DEBIAN_PACKAGE_SECTION "science")
#set(CPACK_GENERATOR "DEB")

#include(CPack)

#configure_file(neun.pc.in neun.pc @ONLY)
#install(FILES neun.pc DESTINATION pkgconfig)
