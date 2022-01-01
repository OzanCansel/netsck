add_custom_target(
    udp-car-binary
)

add_custom_target(
    udp-car-binary-remote-control
)

add_custom_command(
    TARGET
        udp-car-binary
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        $<TARGET_FILE:netsck> car.js
)

add_custom_command(
    TARGET
        udp-car-binary-remote-control
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        $<TARGET_FILE:netsck> remote-control.js
)