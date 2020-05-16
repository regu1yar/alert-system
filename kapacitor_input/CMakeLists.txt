set_source_files_properties(
        ${RootProtoSources} ${RootProtoHeaders}
        PROPERTIES GENERATED TRUE
)

add_library(kapacitor_input alert_parser.cpp alert_parser.h field_parsers.cpp field_parsers.h)

add_dependencies(kapacitor_input root_proto_generating)

target_sources(kapacitor_input
        PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/alert_handler.cpp"
        "${RootProtoSources}"
        PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/alert_handler.h"
        "${RootProtoHeaders}"
        )

target_include_directories(kapacitor_input PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(kapacitor_input network)
target_link_libraries(kapacitor_input alert_senders)
target_link_libraries(kapacitor_input ${Protobuf_LIBRARIES})

my_target_link_cpprest(kapacitor_input)
