set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

find_package( Qt5Core REQUIRED )
find_package( Qt5Network REQUIRED )
find_package( Qt5Qml REQUIRED )

add_subdirectory( third_party/replxx EXCLUDE_FROM_ALL )
add_subdirectory( third_party/tableprinter EXCLUDE_FROM_ALL )

add_executable( netsck main.cpp
                       doc.qrc
                       shell/shell.hpp
                       shell/shell.cpp
                       shell/js_shell.hpp
                       shell/js_shell.cpp
                       shell/input.hpp
                       shell/input.cpp
                       help/help_doc.hpp
                       help/help_doc.cpp
                       socket/socket.hpp
                       socket/socket.cpp
                       socket/udp_socket.hpp
                       socket/udp_socket.cpp
                       hex/hex_utility.hpp
                       hex/hex_utility.cpp )

target_include_directories( netsck PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                           replxx:replxx )

target_link_libraries( netsck PRIVATE Qt5::Core
                                      Qt5::Network
                                      Qt5::Qml
                                      replxx::replxx
                                      tableprinter::tableprinter )

target_compile_features( netsck PRIVATE cxx_std_17 )