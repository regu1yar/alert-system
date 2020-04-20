target_sources(alert_system
        PRIVATE
        ${MALERTCPPS}
        PUBLIC
        ${MALERTHS}
        )

add_executable(matrix_tester main.cpp)

target_sources(matrix_tester
        PRIVATE
        ${MALERTCPPS}
        PUBLIC
        ${MALERTHS}
        )

target_include_directories(alert_system PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(matrix_tester PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(matrix_tester PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../")

my_target_link_cpprest(matrix_tester)