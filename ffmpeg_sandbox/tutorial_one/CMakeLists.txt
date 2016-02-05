cmake_minimum_required(VERSION 3.0)
project(tutorial_one)

# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)

# make dir
set(MAKE_DIR ${CPP_PROJ_DIR}/make)
include(${MAKE_DIR}/definitions.cmake)

set(PROJ_DIR ${CPP_PROJ_DIR}/ffmpeg_sandbox/tutorial_one_screencap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

file(GLOB SOURCE_FILES ${PROJ_DIR}/src/*.cpp)
#set(SOURCE_FILES ${PROJ_DIR}/src/main.cpp)
#MESSAGE(STATUS "Source variable is: " ${SOURCE_FILES})

set(INCLUDE_DIRS
#  ${PROJ_DIR}/include
  ${BOOST_INC_DIR}
 # ${PROTO_SERVER_DIR}
 )


include_directories(${INCLUDE_DIRS})
link_directories(${BOOST_LIB_DIR})
#MESSAGE(STATUS "Lib variable is: " ${FFMPEG_LIB_DIR})

add_executable(tutorial_one ${SOURCE_FILES})

#add_dependencies(proto-echo-client proto_server)

# linking
#target_link_libraries(tutorial_one z m avcodec avdevice avfilter avformat avutil swscale)
target_link_libraries(tutorial_one avcodec avformat avutil swscale)