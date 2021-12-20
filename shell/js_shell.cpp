#include "js_shell.hpp"
#include <QQmlEngine>
#include <QJSValueIterator>
#include <iostream>
#include "socket/udp_socket.hpp"

js_shell::js_shell()
{
    m_engine.installExtensions( QJSEngine::AllExtensions );

    auto self = m_engine.newQObject( this );
    QJSValueIterator it ( self );

    while ( it.hasNext() )
    {
        it.next();
        m_engine.globalObject()
                .setProperty(
                    it.name().toStdString().c_str() ,
                    it.value()
                );
    }

    QQmlEngine::setObjectOwnership( this , QQmlEngine::CppOwnership );

    m_engine.globalObject().setProperty(
        "udp_socket" ,
        m_engine.newQMetaObject( &udp_socket::staticMetaObject )
    );
}

void js_shell::process( QString line )
{
    using namespace std;
    using namespace std::placeholders;

    auto result = m_engine.evaluate( line );

    if ( result.isError() )
    {
        std::cout << "Uncaught exception. "
                  << result.toString().toStdString()
                  << std::endl;
    }

    emit processed();
}