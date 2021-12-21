#pragma once

#include <QObject>

class hex_utility : public QObject
{

    Q_OBJECT

public:
public slots:

    QByteArray from( const QByteArray& ) const;
    void print( const QByteArray& ) const;

};