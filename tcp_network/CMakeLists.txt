cmake_minimum_required(VERSION 3.3)
project(tcp_network)

set(MAKE_DIR ../make)
include(${MAKE_DIR}/definitions.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES
    src/tcp_server.cpp)

set(INCLUDE_DIRS
    include
    ${BOOST_INC_DIR}
)

include_directories(${INCLUDE_DIRS})

add_library(tcp_net ${SOURCE_FILES})