# boost.cmake

# boost path
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(BOOST_INC_DIR /usr/local/opt/boost/include)
  set(BOOST_LIB_DIR /usr/local/opt/boost/lib)
  set(BOOST_THREAD boost_thread-mt)
  set(OPENSSL_INC_DIR /usr/local/opt/openssl/include)
  set(OPENSSL_LIB_DIR /usr/local/opt/openssl/lib)
endif ()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  if (NOT DEFINED BOOST_INC_DIR)
    set(BOOST_INC_DIR /usr/local/include)
  endif ()
  if (NOT DEFINED BOOST_LIB_DIR)
    set(BOOST_LIB_DIR /usr/local/lib)
  endif()
  set(BOOST_THREAD boost_thread)
  set(OPENSSL_INC_DIR /usr/local/include)
  set(OPENSSL_LIB_DIR /usr/local/lib)
endif ()

message("Boost include location: ${BOOST_INC_DIR}")
message("Boost library location: ${BOOST_LIB_DIR}")
