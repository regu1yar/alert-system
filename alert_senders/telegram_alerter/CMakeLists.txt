target_sources(alert_system
        PRIVATE
        ${TELEGRAMALERTCPPS}
        PUBLIC
        ${TELEGRAMALERTHS}
)

target_include_directories(alert_system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
