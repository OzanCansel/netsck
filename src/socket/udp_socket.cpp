#include "udp_socket.hpp"
#include <QNetworkDatagram>
#include <QVariantMap>
#include <iostream>

udp_socket::udp_socket()
    :   socket { m_sck }
{
    connect(
        &m_sck ,
        &QUdpSocket::readyRead ,
        this ,
        &udp_socket::datagram
    );
}

bool udp_socket::has_datagram()
{
    bool pending {
        m_sck.state() == QAbstractSocket::BoundState &&
        m_sck.hasPendingDatagrams()
    };

    if ( stdout_enabled() )
        std::cout << ( pending ? "Yes" : "No" ) << std::endl;

    return pending;
}

void udp_socket::clear()
{
    int count {};

    while ( m_sck.hasPendingDatagrams() )
    {
        m_sck.receiveDatagram();
        ++count;
    }

    if ( stdout_enabled() )
        std::cout << count << " datagrams cleared." << std::endl;
}

QVariant udp_socket::read_datagram()
{
    if ( m_sck.state() != QAbstractSocket::BoundState ||
         !m_sck.hasPendingDatagrams() )
        return QVariant {};

    auto datagram = m_sck.receiveDatagram();

    QVariantMap value;

    value.insert( "sender_addr" , datagram.senderAddress().toString() );
    value.insert( "sender_port" , datagram.senderPort() );
    value.insert( "dest_addr"   , datagram.destinationAddress().toString() );
    value.insert( "dest_port"   , datagram.destinationPort() );
    value.insert( "data"        , datagram.data() );
    value.insert( "data_utf8"   , QString::fromUtf8( datagram.data() ) );
    value.insert( "hop_limit"   , datagram.hopLimit() );
    value.insert( "iface_idx"   , datagram.interfaceIndex() );

    return value;
}

qint64 udp_socket::send( QByteArray data , QString dst , int dst_port )
{
    auto bytes_written = m_sck.writeDatagram(
        data ,
        QHostAddress { dst } ,
        dst_port
    );

    if ( stdout_enabled() )
        std::cout << bytes_written
                  << " bytes written to "
                  << dst.toStdString()
                  << ":"
                  << dst_port
                  << std::endl;

    return bytes_written;
}