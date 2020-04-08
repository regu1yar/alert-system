target_sources(alert-system
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/abstract_sender.hpp
)

target_include_directories(alert-system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory(matrix_alerter)
add_subdirectory(telegram_alerter)
