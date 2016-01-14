cmake_minimum_required(VERSION 3.0)
project(sipuseragent)

set(MAKE_DIR ../make)
include(${MAKE_DIR}/definitions.cmake)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -std=c++11")

set(SOURCE_FILES ${GLOB_SRC_FILES})

set(INCLUDE_DIRS
    include
    ${BOOST_INCLUDE_DIR}
    ${RESIP_DIR}
    )

include_directories(${INCLUDE_DIRS})

add_library(sipuseragent ${SOURCE_FILES})
