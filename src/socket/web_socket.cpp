#include "web_socket.hpp"
#include <QEventLoop>
#include <QTimer>
#include <iostream>

web_socket::web_socket()
{
    connect(
        &m_sck ,
        &QWebSocket::binaryMessageReceived ,
        this ,
        &web_socket::queue_binary_message
    );
    connect(
        &m_sck ,
        &QWebSocket::textMessageReceived ,
        this ,
        &web_socket::queue_text_message
    );
}

void web_socket::connect_to( QUrl url ) noexcept
{
    m_sck.open( url );
}

void web_socket::close() noexcept
{
    if ( m_sck.state() != QAbstractSocket::UnconnectedState )
    {
        if ( m_stdout_enabled )
            std::cout << "Closed" << std::endl;

        m_sck.close();
    }
    else
    {
        if ( m_stdout_enabled )
            std::cout << "Already closed" << std::endl;
    }
}

bool web_socket::wait_for_connected( int timeout ) noexcept
{
    if ( m_sck.state() == QAbstractSocket::ConnectedState )
        return true;

    QTimer canceller;

    canceller.setSingleShot( true );
    canceller.setInterval(
        timeout <= 0 ? 1999999999 : timeout
    );
    QEventLoop loop;

    connect(
        &canceller ,
        &QTimer::timeout ,
        &loop ,
        &QEventLoop::quit
    );
    connect(
        &m_sck ,
        &QWebSocket::connected ,
        &loop ,
        &QEventLoop::quit
    );
    connect(
        &m_sck ,
        &QWebSocket::disconnected ,
        &loop ,
        &QEventLoop::quit
    );

    canceller.start();
    loop.exec();

    return m_sck.state() == QAbstractSocket::ConnectedState;
}

bool web_socket::is_connected() const noexcept
{
    auto connected = m_sck.state() == QAbstractSocket::ConnectedState;

    if ( m_stdout_enabled )
        std::cout << (connected ? "Yes" : "No" ) << std::endl;

    return connected;
}

void web_socket::queue_binary_message( const QByteArray& msg )
{
    m_bin_messages.push( msg );
}

void web_socket::queue_text_message( const QString& msg )
{
    m_text_messages.push( msg );
}

bool web_socket::wait( int timeout ) noexcept
{
    if ( !empty( m_bin_messages ) || !empty( m_text_messages ) )
        return true;

    QTimer canceller;

    canceller.setSingleShot( true );
    canceller.setInterval(
        timeout <= 0 ? 1999999999 : timeout
    );
    QEventLoop loop;

    connect(
        &canceller ,
        &QTimer::timeout ,
        &loop ,
        &QEventLoop::quit
    );
    connect(
        &m_sck ,
        &QWebSocket::binaryMessageReceived ,
        &loop ,
        &QEventLoop::quit
    );
    connect(
        &m_sck ,
        &QWebSocket::textMessageReceived ,
        &loop ,
        &QEventLoop::quit
    );

    canceller.start();
    loop.exec();

    return !empty( m_bin_messages ) || !empty( m_text_messages );
}

bool web_socket::wait_a_bit() noexcept
{
    return wait( 100 );
}

bool web_socket::has_bin_msg() const noexcept
{
    bool has { !empty( m_bin_messages ) };

    if ( m_stdout_enabled )
        std::cout << ( has ? "Yes" : "No" ) << std::endl;

    return has;
}

bool web_socket::has_text_msg() const noexcept
{
    bool has { !empty( m_text_messages ) };

    if ( m_stdout_enabled )
        std::cout << ( has ? "Yes" : "No" ) << std::endl;

    return has;
}

QVariant web_socket::read_bin_msg()
{
    if ( empty( m_bin_messages ) )
    {
        if ( m_stdout_enabled )
            std::cout << "There is no binary message"
                      << std::endl;

        return QVariant {};
    }

    auto bin_msg = m_bin_messages.front();
    m_bin_messages.pop();

    return bin_msg;
}

QVariant web_socket::read_text_msg()
{
    if ( empty( m_text_messages ) )
    {
        if ( m_stdout_enabled )
            std::cout << "There is no text message"
                      << std::endl;

        return QVariant {};
    }

    auto text_msg = m_text_messages.front();
    m_text_messages.pop();

    return text_msg;
}

bool web_socket::send_bin_msg( QByteArray data ) noexcept
{
    if ( m_sck.state() != QAbstractSocket::ConnectedState )
        return false;

    auto n_bytes = m_sck.sendBinaryMessage( data );

        if ( m_stdout_enabled )
            std::cout << n_bytes << " bytes are sent to "
                      << m_sck.peerAddress().toString().toStdString()
                      << ":"
                      << m_sck.peerPort()
                      << std::endl;


    return n_bytes;
}

bool web_socket::send_text_msg( QString text ) noexcept
{
    if ( m_sck.state() != QAbstractSocket::ConnectedState )
        return false;

    auto n_bytes = m_sck.sendTextMessage( text );

    if ( m_stdout_enabled )
        std::cout << n_bytes << " bytes are sent to "
                  << m_sck.peerAddress().toString().toStdString()
                  << ":"
                  << m_sck.peerPort()
                  << std::endl;

    return n_bytes;
}

void web_socket::enable_stdout( bool enabled ) noexcept
{
    m_stdout_enabled = enabled;
}

bool web_socket::stdout_enabled() const noexcept
{
    return m_stdout_enabled;
}