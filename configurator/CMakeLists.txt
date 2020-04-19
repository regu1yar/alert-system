target_sources(alert_system
        PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/configurator_service.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/recipient.cpp"
        PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/configurator_service.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/recipient.hpp"
)

target_include_directories(alert_system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
