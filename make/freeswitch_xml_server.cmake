

include(${MAKE_DIR}/proto_server.cmake)

set(PROJ_DIR ${PROTO_SERVER_SAMPLES_SERVERS_DIR}/freeswitch_xml_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

file(GLOB SOURCE_FILES ${PROJ_DIR}/src/*.cpp)

set(INCLUDE_DIRS
  ${PROJ_DIR}/include
  ${BOOST_INC_DIR}
  ${PROTO_SERVER_DIR}
)

include_directories(${INCLUDE_DIRS})
link_directories(${LIB_DIR} ${BOOST_LIB_DIR})

add_executable(freeswitch-xml-server ${SOURCE_FILES})

add_dependencies(freeswitch-xml-server proto_server)

# linking
target_link_libraries(freeswitch-xml-server boost_system boost_thread pthread proto_server)