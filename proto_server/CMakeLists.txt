cmake_minimum_required(VERSION 3.3)
project(proto_server)

set(MAKE_DIR ../make)
include(${MAKE_DIR}/definitions.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(CORE_DIR ${PROTO_SERVER_DIR}/core)
set(SOURCE_FILES
        ${CORE_DIR}/proto_net_data.cpp
        ${CORE_DIR}/proto_io_object.cpp
        ${CORE_DIR}/proto_server.cpp
        ${CORE_DIR}/proto_tcp_server.cpp
        ${CORE_DIR}/proto_tcp_session.cpp
)

set(INCLUDE_DIRS
        ${PROTO_SERVER_DIR}
        ${BOOST_INC_DIR}
)

include_directories(${INCLUDE_DIRS})

add_library(proto_server ${SOURCE_FILES})