#pragma once

#include <QWebSocket>
#include <QUrl>
#include <queue>

class web_socket : public QObject
{

    Q_OBJECT

public:

    Q_INVOKABLE web_socket();

public slots:

    void connect_to( QUrl ) noexcept;
    void close() noexcept;
    bool wait_for_connected( int timeout = 5000 ) noexcept;
    bool is_connected() const noexcept;
    bool wait( int timeout = -1 ) noexcept;
    bool wait_a_bit() noexcept;
    bool has_bin_msg() const noexcept;
    bool has_text_msg() const noexcept;
    QVariant read_bin_msg();
    QVariant read_text_msg();
    bool send_bin_msg( QByteArray ) noexcept;
    bool send_text_msg( QString ) noexcept;
    void enable_stdout( bool enabled = true ) noexcept;
    bool stdout_enabled() const noexcept;

private:

    void connected();
    void disconnected();

private slots:

    void queue_binary_message( const QByteArray& );
    void queue_text_message( const QString& );

private:

    bool m_stdout_enabled { true };
    std::queue<QByteArray> m_bin_messages;
    std::queue<QString>    m_text_messages;
    QWebSocket             m_sck;
};