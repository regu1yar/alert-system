add_library(alert_senders)

SET(MALERTCPPS
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_factory.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_prepared_alert.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_preparer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_sender.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/alert.cpp"
        )

SET(MALERTHS
        "${CMAKE_CURRENT_LIST_DIR}/abstract_sender.hpp"
        "${CMAKE_CURRENT_LIST_DIR}/alert.h"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_factory.h"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_prepared_alert.h"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_preparer.h"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_sender.h"
        )

SET(TALERTCPPS
        "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter/telegram.cpp"
        )
SET(TALERTHS
        "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter/telegram.hpp"
        )

target_sources(alert_senders
        PRIVATE
        ${MALERTCPPS}
        ${TALERTCPPS}
        PUBLIC
        ${TALERTHS}
        ${MALERTHS}
        )

target_include_directories(alert_senders PUBLIC "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter" "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter")

my_target_link_cpprest(alert_senders)

target_sources(alert_system
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/abstract_sender.hpp
)

target_include_directories(alert_system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory(matrix_alerter)
add_subdirectory(telegram_alerter)
