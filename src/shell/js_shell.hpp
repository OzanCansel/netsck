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
    int  run( QString file_path );
    void stdout( QJSValue );
    void dump( QJSValue );
    void sleep( int );
    double now();
    int  wait_key( int timeout = 33 );
    QString read_line();
    QJSValue array( QByteArray );
    QVariant flat( QJSValue );
    QJSValue beint16( int );
    QJSValue beint32( int );
    QJSValue beint64( double );
    QJSValue befloat( float );
    QJSValue bedouble( double );
    QJSValue leint16( int );
    QJSValue leint32( int );
    QJSValue leint64( double );
    QJSValue lefloat( float );
    QJSValue ledouble( double );
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