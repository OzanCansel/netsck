#include "hex_utility.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <array>
#include <tableprinter/tableprinter.hpp>

QByteArray hex_utility::from( const QByteArray& data ) const
{
    return QByteArray::fromHex( data );
}

void hex_utility::print( const QByteArray& data ) const
{
    using namespace tableprinter;

    int padding = std::log10( std::size( data ) ) + 2;
    int col_len = 3;

    printer p
    {
        {
            { name { "|" } , width { padding } , right {} } ,
            { name { "0" } , width { col_len } } ,
            { name { "1" } , width { col_len } } ,
            { name { "2" } , width { col_len } } ,
            { name { "3" } , width { col_len } } ,
            { name { "4" } , width { col_len } } ,
            { name { "5" } , width { col_len } } ,
            { name { "6" } , width { col_len } } ,
            { name { "7" } , width { col_len } } ,
            { name { "8" } , width { col_len } } ,
            { name { "9" } , width { col_len } } ,
            { name { "|" } , width { padding } , left {} }
        } ,
        std::cout
    };

    auto rows = extract_rows( data );
    std::string seperator (
        2 * padding + COLS * col_len ,
        '-'
    );

    p.print_headers()
     .echo( seperator );

    for ( const auto& r : rows )
    {
        p.print(
            std::to_string( r.idx ) + '|' ,
            r.cols[ 0 ] ,
            r.cols[ 1 ] ,
            r.cols[ 2 ] ,
            r.cols[ 3 ] ,
            r.cols[ 4 ] ,
            r.cols[ 5 ] ,
            r.cols[ 6 ] ,
            r.cols[ 7 ] ,
            r.cols[ 8 ] ,
            r.cols[ 9 ] ,
            '|' + std::to_string( r.idx )
        );
    }

    p.echo( seperator )
     .print_headers()
     .flush();
}

std::vector<hex_utility::row> hex_utility::extract_rows( const QByteArray& data ) const
{
    auto hex_data = data.toHex();

    std::vector<row> rows;
    rows.reserve( std::size( data ) / COLS );

    for ( auto i = 0; i < std::size( data ); ++i )
    {
        if ( i % COLS == 0 )
            rows.push_back( row { i / COLS } );

        std::string num {
            hex_data.data() + i * 2 ,
            hex_data.data() + i * 2 + 2
        };

        rows.back().cols[ i % COLS ] = num;
    }

    return rows;
}