cmake_minimum_required(VERSION 3.3)
project(proto_server)

# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)

set(MAKE_DIR ${CPP_PROJ_DIR}/make)
include(${MAKE_DIR}/definitions.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(CORE_DIR ${PROTO_SERVER_DIR}/core)
set(DATA_DIR ${CORE_DIR}/data)
set(SERVER_DIR ${CORE_DIR}/server)
set(CLIENT_DIR ${CORE_DIR}/client)
set(SOURCE_FILES
        ${CORE_DIR}/proto_net_types.cpp
        ${DATA_DIR}/proto_net_data.cpp
        ${SERVER_DIR}/proto_server.cpp
        ${SERVER_DIR}/proto_tcp_server.cpp
        ${SERVER_DIR}/proto_session.cpp
        ${SERVER_DIR}/proto_tcp_session.cpp
        ${CLIENT_DIR}/proto_client.cpp
        ${CLIENT_DIR}/proto_tcp_client.cpp)

set(INCLUDE_DIRS
        ${PROTO_SERVER_DIR}
        ${BOOST_INC_DIR}
)

include_directories(${INCLUDE_DIRS})

add_library(proto_server ${SOURCE_FILES})

# linking
target_link_libraries(proto_server boost_system)