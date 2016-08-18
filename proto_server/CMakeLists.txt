cmake_minimum_required(VERSION 3.0)
project(proto_server)

message("\\x1b[31m;***** This CMakeLists.txt file is for CLion only *****")
# root dir
get_filename_component(ROOT_DIR ".." ABSOLUTE)
MESSAGE("Project root directory location: ${ROOT_DIR}")

set(MAKE_DIR ${ROOT_DIR}/make)

include(${MAKE_DIR}/proto_server.cmake)