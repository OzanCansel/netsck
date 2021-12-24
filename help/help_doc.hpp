#pragma once

#include <QString>
#include <QDir>

class help_doc
{
public:

    help_doc();
    QString file_path( const QString& topic ) const;
    bool exists( const QString& topic ) const;

private:

    void prepare();
    QDir doc_directory() const;
};