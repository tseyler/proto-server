cmake_minimum_required(VERSION 3.3)
project(http_server)

# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)

# make dir
set(MAKE_DIR ${CPP_PROJ_DIR}/make)

include(${MAKE_DIR}/definitions.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES
    http_server.cpp
    http_session.cpp
    main.cpp)

set(INCLUDE_DIRS
        include
        ${BOOST_INC_DIR}
        ${TCP_NET_INC_DIR}
        ${NET_PROT_INC_DIR}
)

include_directories(${INCLUDE_DIRS} ${BOOST_INC_DIR})
link_directories(${BIN_DIR} ${BOOST_LIB_DIR})

add_executable(http-server ${SOURCE_FILES})

# linking
target_link_libraries(http-server tcp_net net_protocol boost_regex boost_program_options boost_system)