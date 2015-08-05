cmake_minimum_required(VERSION 3.2)
project(net_protocol)

set(MAKE_DIR ../make)
include(${MAKE_DIR}/definitions.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/http_header_fields.cpp
    src/http_headers.cpp
    src/http_message.cpp
    src/http_parse_routines.cpp
    src/http_request_handler.cpp
    src/http_request_message.cpp
    src/http_request_parser.cpp
    src/http_response_message.cpp
    src/http_response_parser.cpp
    src/http_status_code.cpp
    src/net_data.cpp
    src/net_parse_routines.cpp
)

set(INCLUDE_DIRS
    include
    ${BOOST_INCLUDE_DIR}
)

include_directories(${INCLUDE_DIRS})

add_library(net_protocol ${SOURCE_FILES})