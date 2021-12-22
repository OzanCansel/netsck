#pragma once

#include <QJSEngine>

class js_shell : public QObject
{

    Q_OBJECT

public:

    js_shell();

public slots:

    void help();
    void run( QString file_path );
    void dump( QJSValue );
    void process( QString );

signals:

    void processed();

private:

    void print_if_error( QJSValue );
    void inject_self();
    void inject_classes();

    QJSEngine m_engine;
};