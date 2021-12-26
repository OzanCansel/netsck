#include "help_doc.hpp"
#include <QFileInfo>
#include <QStandardPaths>
#include <QtGlobal>
#include <iostream>

help_doc::help_doc()
{
    prepare();
}

QString help_doc::file_path( const QString& topic ) const
{
#ifdef Q_OS_WIN
    return doc_directory().filePath(
        "netsck-js-api.pdf"
    );
#else
    return doc_directory().filePath(
        QString { topic }.append( ".7" ).toLower()
    );
#endif
}

bool help_doc::exists( const QString& topic ) const
{
#ifdef Q_OS_WIN
    return true;
#else
    return QFileInfo::exists( file_path( topic ) );
#endif
}

void help_doc::prepare()
{
    try
    {
        QDir rcc_doc_dir { ":/doc" };
        QDir local_doc_dir = doc_directory();

        local_doc_dir.removeRecursively();
        local_doc_dir = doc_directory();

        auto man_page_paths = rcc_doc_dir.entryInfoList(
            { "*.7" , "*.pdf" } ,
            QDir::NoDotAndDotDot | QDir::Files
        );

        for ( const QFileInfo path : man_page_paths )
        {
            QFile::copy(
                path.filePath() ,
                local_doc_dir.filePath( path.fileName() )
            );
        }
    }
    catch ( const std::runtime_error& err )
    {
        std::cout << "Error occurred while preparing man pages."
                  << "Message : "
                  << err.what()
                  << std::endl;
    }
}

QDir help_doc::doc_directory() const
{
    auto locs = QStandardPaths::standardLocations(
        QStandardPaths::AppDataLocation
    );

    if ( std::empty( locs ) )
    {
        throw std::runtime_error {
            "Could not find app data location."
        };
    }
    else
    {
        auto app_data_path { locs.front() };

        if ( !QFileInfo::exists( app_data_path ) )
            QDir {}.mkpath( app_data_path );

        QDir doc_dir { app_data_path };

        if ( !QFileInfo::exists( doc_dir.filePath( "man" ) ) )
            doc_dir.mkdir( "man" );

        doc_dir.cd( "man" );

        return doc_dir;
    }
}