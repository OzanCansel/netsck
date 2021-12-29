#pragma once

#include <QJSEngine>
#include <QDir>
#include "help/help_doc.hpp"

class js_shell : public QObject
{

    Q_OBJECT

public:

    js_shell();

public slots:

    void help( QString topic = QString { "netsck" } );
    void run( QString file_path );
    void dump( QJSValue );
    void sleep( int );
    QJSValue array( QByteArray );
    QVariant flat( QJSValue );
    int  wait_key( int timeout = 33 );
    void process( QString );

signals:

    void processed();

private:

    void print_if_error( QJSValue );
    void inject_self();
    void inject_classes();
    void inject_constants();

    help_doc m_doc;
    QJSEngine m_engine;
};