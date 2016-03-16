
include(${MAKE_DIR}/definitions.cmake)

set(PROJ_DIR ${PROTO_SERVER_SAMPLES_CLIENTS_DIR}/control4_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

file(GLOB SOURCE_FILES ${PROJ_DIR}/src/*.cpp)

set(INCLUDE_DIRS
  ${PROJ_DIR}/include
  ${BOOST_INC_DIR}
  ${PROTO_SERVER_DIR}
)

include_directories(${INCLUDE_DIRS})
link_directories(${LIB_DIR} ${BOOST_LIB_DIR})

add_executable(control4-client ${SOURCE_FILES})

add_dependencies(control4-client proto_server)

# linking
target_link_libraries(control4-client boost_system boost_thread boost_regex pthread boost_program_options proto_server)