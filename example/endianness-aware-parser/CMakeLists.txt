add_custom_target(
    endianness-aware-parser
)

add_custom_command(
    TARGET
        endianness-aware-parser
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        $<TARGET_FILE:netsck> parser.js
)