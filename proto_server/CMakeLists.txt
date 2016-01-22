cmake_minimum_required(VERSION 3.0)
project(proto_server)

# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)

set(MAKE_DIR ${CPP_PROJ_DIR}/make)

include(${MAKE_DIR}/proto_server.cmake)