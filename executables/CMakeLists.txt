cmake_minimum_required(VERSION 3.10)

set_source_files_properties(
        ${RootProtoSources} ${RootProtoHeaders}
        PROPERTIES GENERATED TRUE
)

add_executable(test_full_delivery test_full_delivery.cpp)
target_include_directories(test_full_delivery PUBLIC "${CMAKE_CURRENT_LIST_DIR}/../")
target_link_libraries(test_full_delivery network)
target_link_libraries(test_full_delivery kapacitor_input)
my_target_link_cpprest(test_full_delivery)
