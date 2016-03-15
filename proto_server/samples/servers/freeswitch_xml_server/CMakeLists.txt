cmake_minimum_required(VERSION 3.0)
project(freeswitch_xml_server)

# root dir
get_filename_component(ROOT_DIR "../../../../" ABSOLUTE)
MESSAGE("Project root directory location: ${ROOT_DIR}")

set(MAKE_DIR ${ROOT_DIR}/make)
include(${MAKE_DIR}/freeswitch_xml_server.cmake)
include(${MAKE_DIR}/proto_server.cmake)

add_dependencies(freeswitch-xml-server proto_server)