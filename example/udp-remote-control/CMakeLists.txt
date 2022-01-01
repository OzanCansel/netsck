add_custom_target(
    vehicle
)

add_custom_target(
    remote-control
)

add_custom_command(
    TARGET
        vehicle
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        $<TARGET_FILE:netsck> vehicle.js
)

add_custom_command(
    TARGET
        remote-control
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND
        $<TARGET_FILE:netsck> remote-control.js
)