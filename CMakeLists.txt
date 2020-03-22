cmake_minimum_required(VERSION 3.15)
project(alert_system)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_COMPILER "clang++")

include_directories("/usr/local/Cellar/cpprestsdk/2.10.15/include")
include_directories("/usr/local/Cellar/boost/1.72.0/include")
include_directories("/usr/local/Cellar/openssl/1.0.2r/include")

link_directories("/usr/local/Cellar/openssl/1.0.2r/lib/")
link_directories("/usr/local/Cellar/cpprestsdk/2.10.15/lib")
link_directories("/usr/local/Cellar/boost/1.72.0/lib")

link_libraries(ssl crypto boost_system boost_thread-mt boost_chrono-mt cpprest)

set(SOURCE_FILES network/controllers/basic_controller.cpp
                 network/network_utils.cpp
                 network/controllers/router_controller.cpp)

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})
set(ROUTER_EXAMPLE "router_example")
add_executable(${ROUTER_EXAMPLE} network/examples/router_example/main.cpp ${SOURCE_FILES})

set(PROJECT_INCLUDE_DIRS "network" "network/controllers")
include_directories(${PROJECT_INCLUDE_DIRS})

#
## Configure required libraries ...
#if(UNIX) # Darwing or Linux
#
#  set(Boost_USE_MULTITHREADED TRUE)
#  find_package(Boost REQUIRED COMPONENTS system thread log program_options chrono)
#  find_package(Threads REQUIRED)
#  find_package(cpprestsdk REQUIRED)
#
#  if(APPLE)
#    # Prefer a homebrew version of OpenSSL over the one in /usr/lib
#    file(GLOB OPENSSL_ROOT_DIR /usr/local/Cellar/openssl/*)
#    # Prefer the latest (make the latest one first)
#    list(REVERSE OPENSSL_ROOT_DIR)
#
#    find_package(OpenSSL 1.0.2 REQUIRED)
#    set(OPENSSL_VERSION "1.0.2p")
#  else()
#    find_package(OpenSSL 1.0.1 REQUIRED)
#    set(OPENSSL_VERSION "1.0.1")
#  endif()
#
#elseif(WIN32) # Windows systems including Win64.
#  message(FATAL_ERROR "-- Windows is not supported for now.")
#else()
#  message(FATAL_ERROR "-- Unsupported platform sorry! :( ")
#endif()
#
#set(LINK_FLAGS "-lssl -lcrypto -L/usr/local/Cellar/openssl/1.0.2r/lib")
#
## Configure compiler options ...
#if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#
#  message("-- configuring clang options")
#  set(CMAKE_CXX_FLAGS "-arch x86_64 -std=c++11 -stdlib=libc++ -DBOOST_LOG_DYN_LINK -Wno-deprecated-declarations ${LINK_FLAGS}")
#
#elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
#
#  message("-- configuring gcc options")
#
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -DBOOST_LOG_DYN_LINK ${LINK_FLAGS}")
#
#endif()
#
#include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
#
#add_executable(${PROJECT_NAME} main.cpp
#                               network/controllers/basic_controller.cpp
#                               network/network_utils.cpp
#                               network/controllers/router_controller.cpp)
#set(ROUTER_EXAMPLE "router_example")
#add_executable(${ROUTER_EXAMPLE} network/examples/main.cpp
#                              network/controllers/basic_controller.cpp
#                              network/network_utils.cpp
#                              network/controllers/router_controller.cpp)
#
## headers search paths ...
#set(CPPRESTSDK_INCLUDE_DIR "/usr/local/include/cpprest")
#set(PROJECT_INCLUDE_DIRS "network" "network/controllers")
#message(PROJECT_INCLUDE_DIRS " ${PROJECT_INCLUDE_DIRS}")
#set(HEADER_SEARCH_PATHS ${CPPRESTSDK_INCLUDE_DIR} ${PROJECT_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})
#
## library search paths ...
#if(APPLE)
#  set(OPENSSL_LIBS "/usr/local/Cellar/openssl/${OPENSSL_VERSION}/lib/libssl.1.0.0.dylib;/usr/local/Cellar/openssl/${OPENSSL_VERSION}/lib/libcrypto.1.0.0.dylib")
#  set(CPPRESTSDK_LIBRARY "${PROJECT_SOURCE_DIR}/libs/cpprestsdk/build.release/Binaries/libcpprest.a")
##  set(ZIP_LIBRARY "/usr/local/Cellar/zlib/1.2.11/lib/libz.dylib")
#
#  set(LIBRARIES_SEARCH_PATHS ${OPENSSL_LIBS} ${Boost_LIBRARIES} ${CPPRESTSDK_LIBRARY} ${ZIP_LIBRARY})
#else()
#  set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
#  set(CPPRESTSDK_LIBRARY "${PROJECT_SOURCE_DIR}/libs/cpprestsdk/build.release/Binaries/libcpprest.a")
#
#  set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${Boost_LIBRARIES})
#endif()
#
#message(BOOST_LIBS " ${Boost_LIBRARIES}")
#message(OPENSSL_LIBS " ${OPENSSL_LIBRARIES}")
#message(CPPRESTSDK_LIBRARY " ${CPPRESTSDK_LIBRARY}")
#message(LIBRARIES_SEARCH_PATHS " ${LIBRARIES_SEARCH_PATHS}")
#
#include_directories(${HEADER_SEARCH_PATHS})
#if (APPLE)
#  target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation")
#  target_link_libraries(${PROJECT_NAME} "-framework Security")
#  target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})
#  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-W1, -F/Library/Frameworks")
#
##  target_link_libraries(${ROUTER_EXAMPLE} "-framework CoreFoundation")
##  target_link_libraries(${ROUTER_EXAMPLE} "-framework Security")
##  target_link_libraries(${ROUTER_EXAMPLE} ${LIBRARIES_SEARCH_PATHS})
##  set_target_properties(${ROUTER_EXAMPLE} PROPERTIES LINK_FLAGS "-W1, -F/Library/Frameworks")
#else()
#  target_link_libraries(${PROJECT_NAME} ${LIBRARIES_SEARCH_PATHS})
#endif()