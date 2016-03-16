cmake_minimum_required(VERSION 3.0)
project(control4_client)

# root dir
get_filename_component(ROOT_DIR "../../../../" ABSOLUTE)
MESSAGE("Project root directory location: ${ROOT_DIR}")


set(MAKE_DIR ${ROOT_DIR}/make)
include(${MAKE_DIR}/control4_client.cmake)
include(${MAKE_DIR}/proto_server.cmake)

add_dependencies(control4-client proto_server)