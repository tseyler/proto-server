cmake_minimum_required(VERSION 3.3)
project(proto_echo_server)

# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)

set(MAKE_DIR ${CPP_PROJ_DIR}/make)
include(${MAKE_DIR}/definitions.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES main.cpp proto_echo_io.cpp)

set(INCLUDE_DIRS
        ${BOOST_INC_DIR}
        ${PROTO_SERVER_DIR}
)

include_directories(${INCLUDE_DIRS})
link_directories(${BIN_DIR} ${BOOST_LIB_DIR})

add_executable(proto-echo-server ${SOURCE_FILES})

# linking
target_link_libraries(proto-echo-server boost_system proto_server)