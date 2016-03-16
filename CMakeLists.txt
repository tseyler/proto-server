cmake_minimum_required(VERSION 3.0)
project(proto_server_all)

# root dir
get_filename_component(ROOT_DIR "." ABSOLUTE)
MESSAGE("Project root directory location: ${ROOT_DIR}")

set(MAKE_DIR ${ROOT_DIR}/make)

include(${MAKE_DIR}/proto_server.cmake)
include(${MAKE_DIR}/proto_server_test.cmake)
include(${MAKE_DIR}/proto_echo_client.cmake)
include(${MAKE_DIR}/proto_echo_server.cmake)
include(${MAKE_DIR}/proto_echo_server_client.cmake)
include(${MAKE_DIR}/freeswitch_xml_server.cmake)
include(${MAKE_DIR}/control4_client.cmake)