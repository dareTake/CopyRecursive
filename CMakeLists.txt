cmake_minimum_required(VERSION 3.5)
project(CopyRecursive)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" )
endif()
install(DIRECTORY DESTINATION bin)

add_subdirectory(src)


