#pragma once

#include <QAbstractSocket>

class socket : public QObject
{

    Q_OBJECT

public:

    socket( QAbstractSocket& );

public slots:

    bool stdout_enabled() const noexcept;
    void enable_stdout( bool enabled = true ) noexcept;
    QString addr() const noexcept;
    int port() const noexcept;
    void close() noexcept;
    bool bind(
        QString addr ,
        int port = 0 ,
        QAbstractSocket::BindMode mode = QAbstractSocket::DefaultForPlatform
    ) noexcept;
    bool bind(
        int port = 0 ,
        QAbstractSocket::BindMode mode = QAbstractSocket::DefaultForPlatform
    ) noexcept;
    bool flush( int duration = -1 );
    bool wait( int duration = -1 );
    bool wait_a_bit();
    QAbstractSocket::SocketError error() const noexcept;

private:

    bool m_stdout_enabled { true };
    QAbstractSocket& m_sck;
};