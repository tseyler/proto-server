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
set(BOOST_INC_DIR /usr/local/include)
set(BOOST_LIB_DIR /usr/local/lib)

set(TCP_NET_INC_DIR ${CPP_PROJ_DIR}/tcp_network/include)
set(NET_PROT_INC_DIR ${CPP_PROJ_DIR}/net_protocol/include)
set(PROTO_SERVER_DIR ${CPP_PROJ_DIR}/proto_server)
set(SIPUSERAGENT_INC_DIR ${CPP_PROJ_DIR}/sipuseragent/include)

# resiprocate version
set(RESIP_VERSION 1.10.1)
# resiprocate path
set(RESIP_DIR $ENV{HOME}/resiprocate-${RESIP_VERSION})


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}) 