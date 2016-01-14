cmake_minimum_required(VERSION 3.0)
project(sipuseragent)

set(MAKE_DIR ../make)
include(${MAKE_DIR}/definitions.cmake)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -std=c++11")

set(SOURCE_FILES
  src/UserAgent.cpp
  src/userAgentHelper.cpp
  src/RegistrationHandler.cpp
  src/OutOfDialogHandler.cpp
  src/InviteHandler.cpp
  src/SubscriptionHandler.cpp
  src/PublicationHandler.cpp
  src/MessageHandler.cpp
  src/SessionDialog.cpp
  src/SessionSdp.cpp
)

set(INCLUDE_DIRS
    include
    ${BOOST_INCLUDE_DIR}
    ${RESIP_DIR}
    )

include_directories(${INCLUDE_DIRS})

set(RESIP_DUM_LIB_DIR  ${RESIP_DIR}/resip/dum)
link_directories(${RESIP_DUM_LIB_DIR})


add_library(sipuseragent ${SOURCE_FILES})

#set_target_properties(sipuseragent
 # PROPERTIES
  #ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# linking
target_link_libraries(sipuseragent dum)