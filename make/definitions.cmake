# definitions.cmake

message("CMake System Processor: ${CMAKE_SYSTEM_PROCESSOR}")

# make dir
set(MAKE_DIR ${ROOT_DIR}/make)
message("Project make directory location: ${MAKE_DIR}")

# bin dir
set(BIN_DIR ${ROOT_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_PROCESSOR})
message("Project bin directory location: ${BIN_DIR}")

#set lib dir
set(LIB_DIR ${ROOT_DIR}/lib/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_PROCESSOR})
message("Project lib directory location: ${LIB_DIR}")

# boost path
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(BOOST_INC_DIR /usr/local/opt/boost/include)
set(BOOST_LIB_DIR /usr/local/opt/boost/lib)
set(BOOST_THREAD boost_thread-mt)
set(OPENSSL_INC_DIR /usr/local/opt/openssl/include)
set(OPENSSL_LIB_DIR /usr/local/opt/openssl/lib)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(BOOST_INC_DIR /usr/local/include)
set(BOOST_LIB_DIR /usr/local/lib)
set(BOOST_THREAD boost_thread)
set(OPENSSL_INC_DIR /usr/local/include)
set(OPENSSL_LIB_DIR /usr/local/lib)
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#set(BOOST_INC_DIR /usr/local/include)
#set(BOOST_LIB_DIR /usr/local/lib)

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
