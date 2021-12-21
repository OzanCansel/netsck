#include "js_shell.hpp"
#include <QQmlEngine>
#include <QJSValueIterator>
#include <iostream>
#include "socket/udp_socket.hpp"
#include "hex/hex_utility.hpp"

js_shell::js_shell()
{
    m_engine.installExtensions( QJSEngine::AllExtensions );

    inject_self();
    inject_classes();
}

void js_shell::help()
{
    std::cout << "Unfortunately 'help()' has not implemented yet."
              << std::endl;
}

void js_shell::dump( QJSValue val )
{
    QJSValue fun = m_engine.evaluate(
        "(function( a ) { print( JSON.stringify( a , null , 4 ) ) } )"
    );

    fun.call( QJSValueList { val } );
}

void js_shell::process( QString line )
{
    auto result = m_engine.evaluate( line );

    if ( result.isError() )
    {
        std::cout << "Uncaught exception. "
                  << result.toString().toStdString()
                  << std::endl;
    }

    emit processed();
}

void js_shell::inject_self()
{
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
}

void js_shell::inject_classes()
{
    static hex_utility hex_instance;

    QQmlEngine::setObjectOwnership( &hex_instance , QQmlEngine::CppOwnership );

    m_engine.globalObject().setProperty(
        "Hex" ,
        m_engine.newQObject( &hex_instance )
    );
    m_engine.globalObject().setProperty(
        "udp_socket" ,
        m_engine.newQMetaObject( &udp_socket::staticMetaObject )
    );
}