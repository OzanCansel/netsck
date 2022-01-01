add_custom_target(
    udp-hex-printer-listen
)

add_custom_target(
    udp-hex-printer-send
)

add_custom_command(
    TARGET
        udp-hex-printer-listen
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        $<TARGET_FILE:netsck> listen.js
)

add_custom_command(
    TARGET
    udp-hex-printer-send
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        $<TARGET_FILE:netsck> send.js
)