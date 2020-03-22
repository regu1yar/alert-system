cmake_minimum_required(VERSION 3.15)
project(alert_system)

if(UNIX) # Darwing or Linux

  if(APPLE)
    # Prefer a homebrew version of OpenSSL over the one in /usr/lib
    file(GLOB OPENSSL_ROOT_DIR /usr/local/Cellar/openssl/*)
    # Prefer the latest (make the latest one first)
    list(REVERSE OPENSSL_ROOT_DIR)

    find_package(OpenSSL 1.0.2 REQUIRED)
  else()
    find_package(OpenSSL 1.0.1 REQUIRED)
  endif()

  set(Boost_USE_MULTITHREADED TRUE)
  find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
  find_package(cpprestsdk REQUIRED)

elseif(WIN32) # Windows systems including Win64.
  message(FATAL_ERROR "-- Windows is not supported for now.")
else()
  message(FATAL_ERROR "-- Unsupported platform sorry! :( ")
endif()

# Configure compiler options ...
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

  message("-- configuring clang options")
  set(CMAKE_CXX_FLAGS "-arch x86_64 -std=c++11 -stdlib=libc++ -DBOOST_LOG_DYN_LINK -Wno-deprecated-declarations")

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

  message("-- configuring gcc options")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -DBOOST_LOG_DYN_LINK")

endif()

set(SOURCE_FILES network/server/controllers/basic_controller.cpp
                 network/network_utils.cpp
                 network/server/controllers/router_controller.cpp)

add_executable(get_request_example network/client/examples/get_request_example/main.cpp ${SOURCE_FILES})
add_executable(router_example network/server/examples/router_example/main.cpp ${SOURCE_FILES} network/server/examples/router_example/runtime_utils.h)

# headers search paths ...
set(PROJECT_INCLUDE_DIRS "network" "network/server/controllers")
include_directories(${PROJECT_INCLUDE_DIRS})

# library search paths ...
if(APPLE)
  set(OPENSSL_LIBS "/usr/local/Cellar/openssl/${OPENSSL_VERSION}/lib/libssl.1.0.0.dylib;/usr/local/Cellar/openssl/${OPENSSL_VERSION}/lib/libcrypto.1.0.0.dylib")
  set(CPPRESTSDK_LIBRARY "cpprestsdk::cpprest")

  set(LIBRARIES_SEARCH_PATHS ${OPENSSL_LIBS} ${Boost_LIBRARIES} ${CPPRESTSDK_LIBRARY})
else()
  set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
  set(CPPRESTSDK_LIBRARY "${PROJECT_SOURCE_DIR}/libs/cpprestsdk/build.release/Binaries/libcpprest.a")

  set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${Boost_LIBRARIES})
endif()

message(BOOST_LIBS " ${Boost_LIBRARIES}")
message(OPENSSL_LIBS " ${OPENSSL_LIBS}")
message(CPPRESTSDK_LIBRARY " ${CPPRESTSDK_LIBRARY}")
message(LIBRARIES_SEARCH_PATHS " ${LIBRARIES_SEARCH_PATHS}")

if (APPLE)
  target_link_libraries(get_request_example "-framework CoreFoundation")
  target_link_libraries(get_request_example "-framework Security")
  target_link_libraries(get_request_example ${LIBRARIES_SEARCH_PATHS})
  set_target_properties(get_request_example PROPERTIES LINK_FLAGS "-W1, -F/Library/Frameworks")

  target_link_libraries(router_example "-framework CoreFoundation")
  target_link_libraries(router_example "-framework Security")
  target_link_libraries(router_example ${LIBRARIES_SEARCH_PATHS})
  set_target_properties(router_example PROPERTIES LINK_FLAGS "-W1, -F/Library/Frameworks")
else()
  target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})
  target_link_libraries(router_example ${LIBRARIES_SEARCH_PATHS})
endif()
