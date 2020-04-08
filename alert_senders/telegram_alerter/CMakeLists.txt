target_sources(alert-system
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/telegram.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/telegram.hpp
)

target_include_directories(alert-system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
