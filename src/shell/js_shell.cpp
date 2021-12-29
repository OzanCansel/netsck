#include "js_shell.hpp"
#include <QtGlobal>
#include <QQmlEngine>
#include <QJSValueIterator>
#include <QFile>
#include <QProcess>
#include <QStandardPaths>
#include <QFileInfo>
#include <QAbstractSocket>
#include <QDataStream>
#include <QtEndian>
#include <thread>
#include <iostream>
#include "socket/udp_socket.hpp"
#include "hex/hex_utility.hpp"
#include "input.hpp"

js_shell::js_shell()
{
    m_engine.installExtensions( QJSEngine::AllExtensions );

    inject_self();
    inject_classes();
    inject_constants();
}

void js_shell::help( QString topic )
{
    if ( !m_doc.exists( topic ) )
    {
        std::cout << "Topic '"
                  << topic.toStdString()
                  << "' doesn't exist."
                  << std::endl;

        return;
    }

#ifdef Q_OS_WIN
    QProcess::startDetached(
        "cmd.exe" ,
        { "/c" , m_doc.file_path( topic ) }
    );
#else
    auto command = QString {
        "/bin/man \"%1\""
    }.arg( m_doc.file_path( topic ) )
     .toStdString();

    system( command.c_str() );
#endif
}

void js_shell::run( QString file_path )
{
    if ( !QFile::exists( file_path ) )
    {
        std::cout << '\''
                  << file_path.toStdString()
                  << "' does not exist."
                  << std::endl;

        return;
    }

    QFile script_f { file_path };

    if ( !script_f.open( QIODevice::ReadOnly ) )
    {
        std::cout << "Could not open '"
                  << file_path.toStdString()
                  << "'. Error : "
                  << script_f.errorString().toStdString()
                  << std::endl;

        return;
    }

    auto script = QString::fromUtf8( script_f.readAll() );

    auto result = m_engine.evaluate( script );

    print_if_error( result );
}

void js_shell::dump( QJSValue val )
{
    QJSValue fun = m_engine.evaluate(
        "(function( a ) { print( JSON.stringify( a , null , 4 ) ) } )"
    );

    fun.call( QJSValueList { val } );
}

void js_shell::sleep( int duration_ms )
{
    std::this_thread::sleep_for(
        std::chrono::milliseconds { duration_ms }
    );
}

int js_shell::wait_key( int timeout )
{
    return ::wait_key( timeout );
}

QJSValue js_shell::array( QByteArray data )
{
    auto arr = m_engine.newArray(
        std::size( data )
    );

    for ( auto i = 0; i < std::size( data ); ++i )
        arr.setProperty( i , std::uint8_t( data.at( i ) ) );

    return arr;
}

QVariant js_shell::flat( QJSValue val )
{
    if ( val.isArray() )
    {
        auto size = val.property( "length" ).toInt();

        QByteArray flattened ( size , 0 );

        for ( auto i = 0; i < size; ++i )
        {
            auto prop = val.property( i );

            if ( prop.isNumber() )
            {
                flattened[ i ] = char( prop.toInt() );
            }
            else if ( prop.isString() )
            {
                auto elem = prop.toString();

                if ( std::size( elem ) == 1 )
                    flattened[ i ] = elem.at( 0 ).toLatin1();
            }
        }

        return flattened;
    }

    return QVariant {};
}

QJSValue js_shell::beint16( int value )
{
    QByteArray raw ( 2 , Qt::Uninitialized );

    qToBigEndian(
        quint16( value ) ,
        raw.data()
    );

    return array( raw );
}

QJSValue js_shell::beint32( int value )
{
    QByteArray raw { 4 , Qt::Uninitialized };

    qToBigEndian(
        value ,
        raw.data()
    );

    return array( raw );
}

QJSValue js_shell::beint64( double value )
{
    QByteArray raw { 8 , Qt::Uninitialized };

    qToBigEndian(
        quint64( value ) ,
        raw.data()
    );

    return array( raw );
}

QJSValue js_shell::befloat( float value )
{
    QByteArray raw { 4 , Qt::Uninitialized };

    qToBigEndian(
        value ,
        raw.data()
    );

    return array( raw );
}

QJSValue js_shell::bedouble( double value )
{
    QByteArray raw { 8 , Qt::Uninitialized };

    qToBigEndian(
        value ,
        raw.data()
    );

    return array( raw );
}

QJSValue js_shell::leint16( int value )
{
    QByteArray raw { 2 , Qt::Uninitialized };

    qToLittleEndian(
        quint16( value ) ,
        raw.data()
    );

    return array( raw );
}

QJSValue js_shell::leint32( int value )
{
    QByteArray raw { 4 , Qt::Uninitialized };

    qToLittleEndian(
        value ,
        raw.data()
    );

    return array( raw );
}

QJSValue js_shell::leint64( double value )
{
    QByteArray raw { 8 , Qt::Uninitialized };

    qToLittleEndian(
        quint64( value ) ,
        raw.data()
    );

    return array( raw );
}

QJSValue js_shell::lefloat( float value )
{
    QByteArray raw { 4 , Qt::Uninitialized };

    qToLittleEndian(
        value ,
        raw.data()
    );

    return array( raw );
}

QJSValue js_shell::ledouble( double value )
{
    QByteArray raw { 8 , Qt::Uninitialized };

    qToLittleEndian(
        value ,
        raw.data()
    );

    return array( raw );
}

void js_shell::process( QString line )
{
    auto result = m_engine.evaluate( line );

    print_if_error( result );

    emit processed();
}

void js_shell::print_if_error( QJSValue result )
{
    if ( result.isError() )
    {
        std::cout << "Uncaught exception. '"
                  << result.toString().toStdString()
                  << '\''
                  << std::endl;
    }
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

void js_shell::inject_constants()
{
    auto global { m_engine.globalObject() };

    global.setProperty(
        "LocalHost" ,
        "127.0.0.1"
    );
    global.setProperty(
        "Broadcast" ,
        "255.255.255.255"
    );
    global.setProperty(
        "AnyIPv4" ,
        "0.0.0.0"
    );
    global.setProperty(
        "ShareAddress" ,
        QAbstractSocket::ShareAddress
    );
    global.setProperty(
        "DontShareAddress" ,
        QAbstractSocket::DontShareAddress
    );
    global.setProperty(
        "ReuseAddressHint" ,
        QAbstractSocket::ReuseAddressHint
    );
    global.setProperty(
        "DefaultForPlatorm"  ,
        QAbstractSocket::DefaultForPlatform
    );

    auto key = m_engine.newObject();
    fill_keys( key );
    global.setProperty( "Key" , key );
}