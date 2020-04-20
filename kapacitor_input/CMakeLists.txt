add_library(kapacitor_input)

target_sources(kapacitor_input
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/alert_handler.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/alert_handler.h
        )

target_include_directories(kapacitor_input PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(kapacitor_input network)
target_link_libraries(kapacitor_input alert_senders)


my_target_link_cpprest(kapacitor_input)

target_sources(alert_system
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/alert_handler.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/alert_handler.h
)

target_include_directories(alert_system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
