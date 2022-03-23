#pragma once

#include <QUdpSocket>
#include <queue>
#include "socket.hpp"

class udp_socket : public socket
{

    Q_OBJECT

public:

    Q_INVOKABLE udp_socket();

public slots:

    bool has_datagram();
    QVariant read_datagram();
    void clear();
    qint64 send( QByteArray , QString , int );

signals:

    void datagram();

private:

    QUdpSocket m_sck;
};