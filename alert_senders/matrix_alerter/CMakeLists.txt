target_sources(alert_system
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/matrix_factory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/matrix_prepared_alert.cpp
        ${CMAKE_CURRENT_LIST_DIR}/matrix_preparer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/matrix_sender.cpp
        ${CMAKE_CURRENT_LIST_DIR}/../alert.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/matrix_factory.h
        ${CMAKE_CURRENT_LIST_DIR}/matrix_prepared_alert.h
        ${CMAKE_CURRENT_LIST_DIR}/matrix_preparer.h
        ${CMAKE_CURRENT_LIST_DIR}/matrix_sender.h
        ${CMAKE_CURRENT_LIST_DIR}/../alert.h
        )

add_executable(matrix_tester main.cpp)

target_sources(matrix_tester
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/matrix_factory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/matrix_prepared_alert.cpp
        ${CMAKE_CURRENT_LIST_DIR}/matrix_preparer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/matrix_sender.cpp
        ${CMAKE_CURRENT_LIST_DIR}/../alert.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/matrix_factory.h
        ${CMAKE_CURRENT_LIST_DIR}/matrix_prepared_alert.h
        ${CMAKE_CURRENT_LIST_DIR}/matrix_preparer.h
        ${CMAKE_CURRENT_LIST_DIR}/matrix_sender.h
        ${CMAKE_CURRENT_LIST_DIR}/../alert.h
        ${CMAKE_CURRENT_LIST_DIR}/../abstract_sender.hpp
        )

target_include_directories(alert_system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(matrix_tester PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(matrix_tester PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../")

my_target_link_cpprest(matrix_tester)