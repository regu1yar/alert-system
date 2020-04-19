cmake_minimum_required(VERSION 3.10)
project(alert_system)

if(UNIX) # Darwing or Linux

  if(APPLE)
    # Prefer a homebrew version of OpenSSL over the one in /usr/lib
    file(GLOB OPENSSL_ROOT_DIR /usr/local/Cellar/openssl/*)
    # Prefer the latest (make the latest one first)
    list(REVERSE OPENSSL_ROOT_DIR)

    find_package(OpenSSL 1.0.2 REQUIRED)
  else()
    set(cpprestsdk_DIR /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/)

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
  set(CMAKE_CXX_FLAGS "-std=c++17 -stdlib=libc++")

elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

  message("-- configuring gcc options")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

endif()

# library search paths ...
if(APPLE)
  set(OPENSSL_LIBS "/usr/local/Cellar/openssl/${OPENSSL_VERSION}/lib/libssl.1.0.0.dylib;/usr/local/Cellar/openssl/${OPENSSL_VERSION}/lib/libcrypto.1.0.0.dylib")
  set(CPPRESTSDK_LIBRARY "cpprestsdk::cpprest")

  set(LIBRARIES_SEARCH_PATHS ${OPENSSL_LIBS} ${Boost_LIBRARIES} ${CPPRESTSDK_LIBRARY})
else()
  set(OPENSSL_LIBS "${OPENSSL_LIBRARIES}")
  set(CPPRESTSDK_LIBRARY "cpprestsdk::cpprest")

  set(LIBRARIES_SEARCH_PATHS ${CPPRESTSDK_LIBRARY} ${OPENSSL_LIBS} ${Boost_LIBRARIES})
endif()

message(BOOST_LIBS " ${Boost_LIBRARIES}")
message(OPENSSL_LIBS " ${OPENSSL_LIBS}")
message(CPPRESTSDK_LIBRARY " ${CPPRESTSDK_LIBRARY}")
message(LIBRARIES_SEARCH_PATHS " ${LIBRARIES_SEARCH_PATHS}")

function(my_target_link_cpprest target_name)
  if (APPLE)
    target_link_libraries(${target_name} "-framework CoreFoundation")
    target_link_libraries(${target_name} "-framework Security")
    target_link_libraries(${target_name} ${LIBRARIES_SEARCH_PATHS})
    set_target_properties(${target_name} PROPERTIES LINK_FLAGS "-W1, -F/Library/Frameworks")
  else()
    target_link_libraries(${target_name} ${LIBRARIES_SEARCH_PATHS})
  endif()
endfunction()

set(CMAKE_CXX_CLANG_TIDY clang-tidy;)

add_executable(alert_system main.cpp)

add_subdirectory(executables)
add_subdirectory(third_party/etcd-cpp-apiv3)
add_subdirectory(network)
add_subdirectory(kapacitor_input)
add_subdirectory(alert_senders)
add_subdirectory(configurator)

target_link_libraries(alert_system network)
target_link_libraries(alert_system kapacitor_input)
target_link_libraries(alert_system alert_senders)

my_target_link_cpprest(alert_system)
