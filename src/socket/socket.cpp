#include "socket.hpp"
#include <QHostAddress>
#include <iostream>
#include <mutex>

std::once_flag register_flag;

socket::socket( QAbstractSocket& sck )
    :   m_sck { sck }
{   
    std::call_once(
        register_flag ,
        [](){
            qRegisterMetaType<QAbstractSocket::SocketError>();
        }
    );
}

bool socket::stdout_enabled() const noexcept
{
    return m_stdout_enabled;
}

void socket::enable_stdout( bool enabled ) noexcept
{
    m_stdout_enabled = enabled;
}

QString socket::addr() const noexcept
{
    auto a = m_sck.localAddress().toString();

    if ( stdout_enabled() )
        std::cout << a.toStdString() << std::endl;

    return a;
}

int socket::port() const noexcept
{
    auto p = m_sck.localPort();

    if ( stdout_enabled() )
        std::cout << p << std::endl;

    return p;
}

void socket::close() noexcept
{
    m_sck.close();
}

bool socket::bind(
    QString addr ,
    int port ,
    QAbstractSocket::BindMode mode
) noexcept
{
    auto binded = m_sck.bind(
        QHostAddress { addr } ,
        port ,
        mode
    );

    if ( stdout_enabled() )
    {
        if ( binded )
        {
            std::cout << "Binded to "
                    << addr.toStdString()
                    << ':'
                    << m_sck.localPort()
                    << std::endl;
        }
        else
        {
            std::cout << "Could not binded to "
                    << addr.toStdString()
                    << ':'
                    << port
                    << std::endl;
        }
    }
    
    return binded;
}

bool socket::bind( int port , QAbstractSocket::BindMode mode ) noexcept
{
    return bind( "0.0.0.0" , port , mode );
}

bool socket::flush( int duration )
{
    return m_sck.waitForBytesWritten( duration );
}

bool socket::wait( int duration )
{
    return m_sck.waitForReadyRead( duration );
}

bool socket::wait_a_bit()
{
    return m_sck.waitForReadyRead( 0 );
}

QAbstractSocket::SocketError socket::error() const noexcept
{
    auto error = m_sck.error();

    if ( stdout_enabled() )
        std::cout << m_sck.errorString().toStdString()
                  << std::endl;

    return error;
}