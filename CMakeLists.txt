cmake_minimum_required( VERSION 3.10 )
project( netsck
         VERSION 1.0.0
         HOMEPAGE_URL https://www.github.com/OzanCansel/netsck )

add_subdirectory( src )
add_subdirectory( example )
add_subdirectory( package )

if ( UNIX )
    add_custom_target(
        generate-pdf
        COMMENT
            "Generates pdf documents of man pages."
    )

    add_custom_command(
        TARGET
            generate-pdf
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_SOURCE_DIR}/doc
        COMMAND
            ../script/generate-pdf.sh
    )
endif()
