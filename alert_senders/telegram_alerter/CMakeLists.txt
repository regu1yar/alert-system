target_sources(alert_system
        PRIVATE
        ${TALERTCPPS}
        PUBLIC
        ${TALERTHS}
)

target_include_directories(alert_system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
