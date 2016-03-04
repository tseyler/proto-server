
include(${MAKE_DIR}/definitions.cmake)

# To build a shared library version of proto-server uncomment the following:
#set(BUILD_SHARED_LIBS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(CORE_DIR ${PROTO_SERVER_DIR}/core)
set(DATA_DIR ${CORE_DIR}/data)
set(SERVER_DIR ${CORE_DIR}/server)
set(CLIENT_DIR ${CORE_DIR}/client)
set(FACTORY_DIR ${CORE_DIR}/factory)
set(PROTOCOL_DIR ${CORE_DIR}/protocol)
set(HTTP_DIR ${PROTOCOL_DIR}/http)

file(GLOB CORE_SRC_FILES ${CORE_DIR}/*.cpp)
file(GLOB DATA_SRC_FILES ${DATA_DIR}/*.cpp)
file(GLOB SERVER_SRC_FILES ${SERVER_DIR}/*.cpp)
file(GLOB CLIENT_SRC_FILES ${CLIENT_DIR}/*.cpp)
file(GLOB FACTORY_SRC_FILES ${FACTORY_DIR}/*.cpp)
file(GLOB PROTOCOL_SRC_FILES ${PROTOCOL_DIR}/*.cpp)
file(GLOB HTTP_SRC_FILES ${HTTP_DIR}/*.cpp)

set(SOURCE_FILES
  ${CORE_SRC_FILES}
  ${DATA_SRC_FILES}
  ${SERVER_SRC_FILES}
  ${CLIENT_SRC_FILES}
  ${FACTORY_SRC_FILES}
  ${PROTOCOL_SRC_FILES}
  ${HTTP_SRC_FILES}
  )

set(INCLUDE_DIRS
        ${PROTO_SERVER_DIR}
        ${BOOST_INC_DIR}
)

include_directories(${INCLUDE_DIRS})
		 
add_library(proto_server ${SOURCE_FILES})

#build messages
set(PROTO_SERVER_VERSION "proto-server-0.1.0")
add_custom_command(TARGET proto_server POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan
                   "Build completed: ${PROTO_SERVER_VERSION}")

