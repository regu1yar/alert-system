target_sources(alert-system
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/alert_handler.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/alert_handler.h
)

target_include_directories(alert-system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
