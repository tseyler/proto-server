# definitions.cmake

# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)

# make dir
set(MAKE_DIR ${CPP_PROJ_DIR}/make)

# bin dir
set(BIN_DIR ${CPP_PROJ_DIR}/bin/${CMAKE_BUILD_TYPE})

#set lib dir
set(LIB_DIR ${CPP_PROJ_DIR}/lib/${CMAKE_BUILD_TYPE})

# boost path
IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(BOOST_INC_DIR /usr/local/opt/boost/include)
set(BOOST_LIB_DIR /usr/local/opt/boost/lib)
set(BOOST_THREAD boost_thread-mt)
set(OPENSSL_INC_DIR /usr/local/opt/openssl/include)
set(OPENSSL_LIB_DIR /usr/local/opt/openssl/lib)
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(BOOST_INC_DIR /usr/local/include)
set(BOOST_LIB_DIR /usr/local/lib)
set(BOOST_THREAD boost_thread)
set(OPENSSL_INC_DIR /usr/local/include)
set(OPENSSL_LIB_DIR /usr/local/lib)
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

set(BOOST_INC_DIR /usr/local/include)
set(BOOST_LIB_DIR /usr/local/lib)

set(TCP_NET_INC_DIR ${CPP_PROJ_DIR}/tcp_network/include)
set(NET_PROT_INC_DIR ${CPP_PROJ_DIR}/net_protocol/include)

# proto server
set(PROTO_SERVER_DIR ${CPP_PROJ_DIR}/proto_server)
set(PROTO_SERVER_SAMPLES_DIR ${PROTO_SERVER_DIR}/samples)
set(PROTO_SERVER_SAMPLES_SERVERS_DIR ${PROTO_SERVER_SAMPLES_DIR}/servers)
set(PROTO_SERVER_SAMPLES_CLIENTS_DIR ${PROTO_SERVER_SAMPLES_DIR}/clients)

# sip
set(SIPUSERAGENT_INC_DIR ${CPP_PROJ_DIR}/sipuseragent/include)

# resiprocate version
#set(RESIP_VERSION 1.10.1)
# resiprocate path
#set(RESIP_DIR $ENV{HOME}/resiprocate-${RESIP_VERSION})
# paths to resip libs
#set(RESIP_DUM_LIB_DIR ${RESIP_DIR}/resip/dum/.libs)
#set(RESIP_STACK_LIB_DIR ${RESIP_DIR}/resip/stack/.libs)
#set(RESIP_RUTIL_LIB_DIR ${RESIP_DIR}/rutil/.libs)
#set(RESIP_LIB_DIR ${RESIP_DUM_LIB_DIR} ${RESIP_STACK_LIB_DIR} ${RESIP_RUTIL_LIB_DIR})

# paths to ffmpeg
#set(FFMPEG_ROOT_DIR $ENV{HOME}/ffmpeg_build)
#set(FFMPEG_INC_DIR ${FFMPEG_ROOT_DIR}/include)
#set(FFMPEG_LIB_DIR ${FFMPEG_ROOT_DIR}/lib)

file(GLOB GLOB_SRC_FILES ${CMAKE_BINARY_DIR}/src/*.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}) 