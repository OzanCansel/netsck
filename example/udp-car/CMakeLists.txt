add_custom_target(
    udp-car
)

add_custom_target(
    udp-car-remote-control
)

add_custom_command(
    TARGET
        udp-car
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        $<TARGET_FILE:netsck> car.js
)

add_custom_command(
    TARGET
        udp-car-remote-control
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        $<TARGET_FILE:netsck> remote-control.js
)