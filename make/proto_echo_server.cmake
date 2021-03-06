
include(${MAKE_DIR}/definitions.cmake)

set(PROJ_DIR ${PROTO_SERVER_SAMPLES_SERVERS_DIR}/proto_echo_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

file(GLOB SOURCE_FILES ${PROJ_DIR}/src/*.cpp)

set(INCLUDE_DIRS
  ${PROJ_DIR}/include
  ${BOOST_INC_DIR}
  ${PROTO_SERVER_DIR}
)

include_directories(${INCLUDE_DIRS})
link_directories(${LIB_DIR} ${BOOST_LIB_DIR})

add_executable(proto-echo-server ${SOURCE_FILES})


# linking
target_link_libraries(proto-echo-server boost_system boost_thread boost_regex pthread proto_server)