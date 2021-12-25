#pragma once

#include <QObject>
#include <array>

class hex_utility : public QObject
{

    Q_OBJECT

public:
public slots:

    QByteArray from( const QByteArray& ) const;
    void print( const QByteArray& ) const;

private:

    inline static constexpr int COLS = 10;

    struct row
    {
        int idx;
        std::array<std::string , COLS> cols;
    };

    std::vector<row> extract_rows( const QByteArray& ) const;
};