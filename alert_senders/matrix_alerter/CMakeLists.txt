target_sources(alert_system
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/matrix_alert.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/matrix_alert.h
)

target_include_directories(alert_system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
