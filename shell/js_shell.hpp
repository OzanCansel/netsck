#pragma once

#include <QJSEngine>

class js_shell : public QObject
{

    Q_OBJECT

public:

    js_shell();

public slots:

    void help();
    void process( QString );

signals:

    void processed();

private:

    void inject_self();
    void inject_classes();

    QJSEngine m_engine;
};