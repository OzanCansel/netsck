#include <QCoreApplication>
#include "shell/shell.hpp"
#include "shell/js_shell.hpp"

int main( int argc , char* argv[] )
{
    QCoreApplication app { argc , argv };

    QCoreApplication::setApplicationName( "netsck" );
    QCoreApplication::setApplicationVersion( APP_VERSION );

    if ( argc > 1 )
    {
        js_shell terminal;

        return terminal.run( argv[ 1 ] );
    }

    shell terminal;
    js_shell js_terminal;

    QObject::connect( &terminal    , &shell::input        , &js_terminal , &js_shell::process );
    QObject::connect( &js_terminal , &js_shell::processed , &terminal    , &shell::read_line  );

    return app.exec();
}