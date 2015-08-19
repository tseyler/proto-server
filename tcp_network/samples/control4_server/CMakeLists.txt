cmake_minimum_required(VERSION 3.3)
project(control4_server)

# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)

# make dir
set(MAKE_DIR ${CPP_PROJ_DIR}/make)

include(${MAKE_DIR}/definitions.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES
    control4_server.cpp
    control4_session.cpp
    main.cpp)

set(INCLUDE_DIRS
        include
        ${BOOST_INC_DIR}
        ${TCP_NET_INC_DIR}
        ${NET_PROT_INC_DIR}
)

# directories
include_directories(${INCLUDE_DIRS} ${BOOST_INC_DIR})
link_directories(${BIN_DIR} ${BOOST_LIB_DIR})

add_executable(control4-server ${SOURCE_FILES})

# linking
target_link_libraries(control4-server tcp_net net_protocol boost_program_options boost_system)