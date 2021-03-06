# definitions.cmake


# make dir
set(MAKE_DIR ${ROOT_DIR}/make)
message("Project make directory location: ${MAKE_DIR}")

include(${MAKE_DIR}/boost.cmake)

# set the 32-bit or 64-bit flags
if (NOT DEFINED ARCH_PROCESSOR)
  set(ARCH_PROCESSOR "x86_64")
endif ()

message("Target Processor: ${ARCH_PROCESSOR}")

# bin dir
set(BIN_DIR ${ROOT_DIR}/bin/${CMAKE_BUILD_TYPE}/${ARCH_PROCESSOR})
message("Project bin directory location: ${BIN_DIR}")

#set lib dir
set(LIB_DIR ${ROOT_DIR}/lib/${CMAKE_BUILD_TYPE}/${ARCH_PROCESSOR})
message("Project lib directory location: ${LIB_DIR}")

# boost path
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(BOOST_INC_DIR /usr/local/opt/boost/include)
set(BOOST_LIB_DIR /usr/local/opt/boost/lib)
set(BOOST_THREAD boost_thread-mt)
set(OPENSSL_INC_DIR /usr/local/opt/openssl/include)
set(OPENSSL_LIB_DIR /usr/local/opt/openssl/lib)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

# proto server
set(PROTO_SERVER_DIR ${ROOT_DIR}/proto_server)
message("Project proto server directory location: ${PROTO_SERVER_DIR}")

set(PROTO_SERVER_SAMPLES_DIR ${PROTO_SERVER_DIR}/samples)
set(PROTO_SERVER_SAMPLES_SERVERS_DIR ${PROTO_SERVER_SAMPLES_DIR}/servers)
set(PROTO_SERVER_SAMPLES_CLIENTS_DIR ${PROTO_SERVER_SAMPLES_DIR}/clients)

file(GLOB GLOB_SRC_FILES ${CMAKE_BINARY_DIR}/src/*.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
