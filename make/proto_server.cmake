
include(${MAKE_DIR}/definitions.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(CORE_DIR ${PROTO_SERVER_DIR}/core)
set(DATA_DIR ${CORE_DIR}/data)
set(SERVER_DIR ${CORE_DIR}/server)
set(CLIENT_DIR ${CORE_DIR}/client)
set(FACTORY_DIR ${CORE_DIR}/factory)

file(GLOB CORE_SRC_FILES ${CORE_DIR}/*.cpp)
file(GLOB DATA_SRC_FILES ${DATA_DIR}/*.cpp)
file(GLOB SERVER_SRC_FILES ${SERVER_DIR}/*.cpp)
file(GLOB CLIENT_SRC_FILES ${CLIENT_DIR}/*.cpp)
file(GLOB FACTORY_SRC_FILES ${FACTORY_DIR}/*.cpp)

set(SOURCE_FILES
  ${CORE_SRC_FILES}
  ${DATA_SRC_FILES}
  ${SERVER_SRC_FILES}
  ${CLIENT_SRC_FILES}
  ${FACTORY_SRC_FILES}
  )

set(INCLUDE_DIRS
        ${PROTO_SERVER_DIR}
        ${BOOST_INC_DIR}
)

include_directories(${INCLUDE_DIRS})

add_library(proto_server ${SOURCE_FILES})
