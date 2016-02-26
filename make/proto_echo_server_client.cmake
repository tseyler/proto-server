

include(${MAKE_DIR}/proto_server.cmake)

set(PROJ_DIR ${PROTO_SERVER_SAMPLES_SERVERS_DIR}/proto_echo_server_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

file(GLOB SOURCE_FILES ${PROJ_DIR}/src/*.cpp)

set(INCLUDE_DIRS
  ${PROJ_DIR}/include
  ${BOOST_INC_DIR}
  ${PROTO_SERVER_DIR}
)

include_directories(${INCLUDE_DIRS})
link_directories(${LIB_DIR} ${BOOST_LIB_DIR})

add_executable(proto-echo-server_client ${SOURCE_FILES})

add_dependencies(proto-echo-server_client proto_server)

# linking
target_link_libraries(proto-echo-server_client boost_system boost_thread pthread proto_server)