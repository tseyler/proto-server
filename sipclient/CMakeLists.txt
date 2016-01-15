cmake_minimum_required(VERSION 3.0)
project(sipclient)

set(MAKE_DIR ../make)
include(${MAKE_DIR}/definitions.cmake)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -std=c++11")

set(SOURCE_FILES ${GLOB_SRC_FILES})

set(INCLUDE_DIRS
  include
  ${SIPUSERAGENT_INC_DIR}
  ${BOOST_INCLUDE_DIR}
  ${RESIP_DIR}
  )

include_directories(${INCLUDE_DIRS})

link_directories(${LIB_DIR} ${BOOST_LIB_DIR} ${RESIP_LIB_DIR})

add_executable(sipclient ${SOURCE_FILES})

# linking
target_link_libraries(sipclient sipuseragent boost_system boost_thread dum resip rutil)