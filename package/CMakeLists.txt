set( CPACK_PACKAGE_HOMEPAGE_URL https://www.github.com/OzanCansel/netsck )
set( CPACK_MONOLITHIC_INSTALL TRUE )
set( CPACK_PACKAGE_EXECUTABLES netsck )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Ozan Cansel" )
set( CPACK_PACKAGE_CONTACT "ozancansel@tutanota.com" )
set( CPACK_DEBIAN_PACKAGE_DEPENDS "qtdeclarative5-dev")

include( CPack )

install(
    TARGETS netsck
    DESTINATION bin
)

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