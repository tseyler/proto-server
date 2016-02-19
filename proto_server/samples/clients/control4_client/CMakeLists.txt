cmake_minimum_required(VERSION 3.0)
project(control4_client)

# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)

set(MAKE_DIR ${CPP_PROJ_DIR}/make)
include(${MAKE_DIR}/control4_client.cmake)