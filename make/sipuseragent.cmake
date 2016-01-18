
# cpp-projects dir
set(CPP_PROJ_DIR $ENV{HOME}/projects/cpp-projects)
# make dir
set(MAKE_DIR ${CPP_PROJ_DIR}/make)

include(${MAKE_DIR}/definitions.cmake)

set(PROJ_DIR ${CPP_PROJ_DIR}/sipuseragent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -std=c++11")

file(GLOB SOURCE_FILES ${PROJ_DIR}/src/*.cpp)

set(INCLUDE_DIRS
    ${PROJ_DIR}/include
    ${BOOST_INCLUDE_DIR}
    ${RESIP_DIR}
    )

include_directories(${INCLUDE_DIRS})

add_library(sipuseragent ${SOURCE_FILES})
