cmake_minimum_required(VERSION 3.3)
project(echo_client)

# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)

# make dir
set(MAKE_DIR ${CPP_PROJ_DIR}/make)

include(${MAKE_DIR}/definitions.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(SOURCE_FILES
    main.cpp)

set(INCLUDE_DIRS
        include
        ${BOOST_INC_DIR}
)

include_directories(${INCLUDE_DIRS} ${BOOST_INC_DIR})
link_directories(${BOOST_LIB_DIR})

add_executable(echo-client ${SOURCE_FILES})

# linking
target_link_libraries(echo-client boost_program_options boost_system)