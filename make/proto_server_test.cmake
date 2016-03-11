
include(${MAKE_DIR}/definitions.cmake)
include(${MAKE_DIR}/proto_server.cmake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

set(TEST_DIR ${PROTO_SERVER_DIR}/test)
MESSAGE("Test directory location: ${TEST_DIR}")
file(GLOB TEST_SRC_FILES ${TEST_DIR}/*.cpp)

get_filename_component(PROJECTS_DIR "${PROTO_SERVER_DIR}/../.." ABSOLUTE)
MESSAGE("Projects directory location: ${PROJECTS_DIR}")
set(GOOGLETEST_ROOT_DIR ${PROJECTS_DIR}/googletest)
MESSAGE("Googletest root directory location: ${GOOGLETEST_ROOT_DIR}")
set(GOOGLETEST_DIR ${GOOGLETEST_ROOT_DIR}/googletest)
MESSAGE("Googletest directory location: ${GOOGLETEST_DIR}")
set(GOOGLETEST_INC_DIR ${GOOGLETEST_DIR}/include)
MESSAGE("Googletest include directory location: ${GOOGLETEST_INC_DIR}")
set(GOOGLETEST_SRC_DIR ${GOOGLETEST_DIR}/src)
MESSAGE("Googletest src directory location: ${GOOGLETEST_SRC_DIR}")
file(GLOB GOOGLETEST_SRC_FILES ${GOOGLETEST_SRC_DIR}/.cc)
set(SOURCE_FILES
  ${TEST_SRC_FILES}
 ${GOOGLETEST_SRC_DIR}/gtest_main.cc
  )

set(INCLUDE_DIRS
  #${GOOGLETEST_DIR}
  ${GOOGLETEST_INC_DIR}
  ${PROTO_SERVER_DIR}
  ${BOOST_INC_DIR}
)

include_directories(${INCLUDE_DIRS})
link_directories(${LIB_DIR} ${BOOST_LIB_DIR} ${GOOGLETEST_DIR})

add_executable(proto-server-test ${SOURCE_FILES})

add_dependencies(proto-server-test proto_server)

# linking
target_link_libraries(proto-server-test boost_system boost_thread boost_regex pthread proto_server gtest)

