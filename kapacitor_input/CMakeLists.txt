target_sources(alert_system
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/alert_handler.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/alert_handler.h
)

target_include_directories(alert_system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
