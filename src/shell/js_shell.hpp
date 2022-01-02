#pragma once

#include <QJSEngine>
#include <QDir>
#include <QJSValue>
#include "help/help_doc.hpp"

class js_shell : public QObject
{

    Q_OBJECT

public:

    js_shell();

public slots:

    void help( QString topic = QString { "netsck" } );
    int  run( QString file_path );
    void std_out( QJSValue );
    void dump( QJSValue );
    void sleep( int );
    double now();
    int  wait_key( int timeout = 33 );
    QString read_line();
    QJSValue array( QByteArray );
    QVariant flat( QJSValue );
    QJSValue beint16( QJSValue );
    QJSValue beuint16( QJSValue );
    QJSValue beint32( QJSValue );
    QJSValue beuint32( QJSValue );
    QJSValue beint64( QJSValue );
    QJSValue beuint64( QJSValue );
    QJSValue befloat( QJSValue );
    QJSValue bedouble( QJSValue );
    QJSValue leint16( QJSValue );
    QJSValue leuint16( QJSValue );
    QJSValue leint32( QJSValue );
    QJSValue leuint32( QJSValue );
    QJSValue leint64( QJSValue );
    QJSValue leuint64( QJSValue );
    QJSValue lefloat( QJSValue );
    QJSValue ledouble( QJSValue );
    void process( QString );

signals:

    void processed();

private:

    void print_if_error( QJSValue );
    void inject_self();
    void inject_classes();
    void inject_constants();

    help_doc  m_doc;
    QJSEngine m_engine;
};