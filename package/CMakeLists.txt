set( CPACK_PACKAGE_HOMEPAGE_URL https://www.github.com/OzanCansel/netsck )
set( CPACK_MONOLITHIC_INSTALL TRUE )
set( CPACK_PACKAGE_VENDOR "Ozan Cansel" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Ozan Cansel" )
set( CPACK_PACKAGE_CONTACT "ozancansel@tutanota.com" )
set( CPACK_DEBIAN_PACKAGE_DEPENDS "qtdeclarative5-dev" )

if ( MINGW )
    include( InstallRequiredSystemLibraries )

    set( CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE )
    set( CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\logo.png")
    set( CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/logo.ico" )
    set( CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/logo.ico" )
    set( CPACK_NSIS_MODIFY_PATH "ON" )
    set( CPACK_NSIS_CREATE_ICONS_EXTRA
         "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\netsck.lnk' '$INSTDIR\\\\bin\\\\netsck.exe'" )

    install(
        FILES ../doc/netsck-js-api.pdf
        DESTINATION doc
    )

    install(
        FILES
            ${CMAKE_PREFIX_PATH}/bin/Qt5Core.dll
            ${CMAKE_PREFIX_PATH}/bin/Qt5Network.dll
            ${CMAKE_PREFIX_PATH}/bin/Qt5Qml.dll
            ${CMAKE_PREFIX_PATH}/bin/libgcc_s_seh-1.dll
            ${CMAKE_PREFIX_PATH}/bin/libstdc++-6.dll
            ${CMAKE_PREFIX_PATH}/bin/libwinpthread-1.dll
        DESTINATION bin
    )
else()
    install(
        DIRECTORY ../doc/
        DESTINATION local/share/man/man7
    )

    install(
        FILES ../LICENSE
        DESTINATION local/share/netsck/copyright
    )

    install(
        FILES ../src/third_party/replxx/LICENSE.md
        DESTINATION share/netsck/copyright/replxx
    )
endif()

install(
    TARGETS netsck
    DESTINATION bin
)

include( CPack )
