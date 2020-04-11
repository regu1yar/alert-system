target_sources(alert_system
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/telegram.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/telegram.hpp
)

target_include_directories(alert_system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
