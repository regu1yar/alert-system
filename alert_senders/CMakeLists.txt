add_library(alert_senders)

SET(MATRIXALERTCPPS
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_factory.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_prepared_alert.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_preparer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_sender.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/alert.cpp"
        )

SET(MATRIXALERTHS
        "${CMAKE_CURRENT_LIST_DIR}/abstract_sender.h"
        "${CMAKE_CURRENT_LIST_DIR}/alert.h"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_factory.h"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_prepared_alert.h"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_preparer.h"
        "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter/matrix_sender.h"
        )
SET(TELEGRAMALERTCPPS
        "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter/telegram_factory.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter/telegram_prepared_alert.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter/telegram_preparer.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter/telegram_sender.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/alert.cpp"
        )

SET(TELEGRAMALERTHS
        "${CMAKE_CURRENT_LIST_DIR}/abstract_sender.h"
        "${CMAKE_CURRENT_LIST_DIR}/alert.h"
        "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter/telegram_factory.h"
        "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter/telegram_prepared_alert.h"
        "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter/telegram_preparer.h"
        "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter/telegram_sender.h"
        )

target_sources(alert_senders
        PRIVATE
        ${MATRIXALERTCPPS}
        ${TELEGRAMALERTCPPS}
        PUBLIC
        ${TELEGRAMALERTHS}
        ${MATRIXALERTHS}
        )

target_include_directories(alert_senders PUBLIC "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/telegram_alerter" "${CMAKE_CURRENT_LIST_DIR}/matrix_alerter")

my_target_link_cpprest(alert_senders)

add_subdirectory(matrix_alerter)
add_subdirectory(telegram_alerter)
