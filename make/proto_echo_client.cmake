
# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)
# make dir
set(MAKE_DIR ${CPP_PROJ_DIR}/make)

include(${MAKE_DIR}/definitions.cmake)

set(PROJ_DIR ${PROTO_SERVER_SAMPLES_CLIENTS_DIR}/proto_echo_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

file(GLOB SOURCE_FILES ${PROJ_DIR}/src/*.cpp)

set(INCLUDE_DIRS
  ${BOOST_INC_DIR}
  ${PROTO_SERVER_DIR}
)

include_directories(${INCLUDE_DIRS})
link_directories(${LIB_DIR} ${BOOST_LIB_DIR})

add_executable(proto-echo-client ${SOURCE_FILES})

#add_dependencies(proto-echo-client proto_server)

# linking
target_link_libraries(proto-echo-client boost_system pthread proto_server)