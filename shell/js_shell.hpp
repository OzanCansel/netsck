#pragma once

#include <QJSEngine>

class js_shell : public QObject
{

    Q_OBJECT

public:

    js_shell();

public slots:

    void process( QString );

signals:

    void processed();

private:

    QJSEngine m_engine;
};