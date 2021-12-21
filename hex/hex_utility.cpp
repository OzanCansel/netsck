#include "hex_utility.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

QByteArray hex_utility::from( const QByteArray& data ) const
{
    return QByteArray::fromHex( data );
}

void hex_utility::print( const QByteArray& data ) const
{
    static constexpr int COLS = 10;

    auto col_len              = 3;
    auto data_len             = std::size( data );
    auto left_padding         = int( std::log10( data_len ) ) + 2;
    auto right_padding        = left_padding;
    auto cols                 = std::min( COLS , data_len );
    auto right_edge_remainder = cols - 1;
    auto hex_data             = data.toHex();

    std::cout << std::right
              << std::setw( left_padding )
              << '|';

    for ( auto i = 0; i < cols; ++i )
        std::cout << std::setw( col_len ) << std::to_string( i );

    std::cout << std::setw( right_padding )
              << std::left
              << " |"
              << '\n';

    std::string seperator (
        left_padding +
        cols * col_len +
        right_padding ,
        '-'
    );
    std::cout << seperator << '\n';

    for ( auto i = 0; i < data_len; ++i )
    {
        if ( i % cols == 0 )
            std::cout << std::setw( left_padding )
                      << std::right
                      << std::to_string( i / cols ) + '|';

        std::cout << std::setw( col_len )
                  << std::string {
                        hex_data.data() + i * 2 ,
                        hex_data.data() + i * 2 + 2
                    };

        if ( i % cols != right_edge_remainder && i == data_len - 1 )
            std::cout << std::string ( ( cols - data_len % cols ) * col_len , ' ' );

        if ( i % cols == right_edge_remainder ||
             i == data_len - 1 )
            std::cout << std::setw( right_padding )
                      << std::left
                      << " |" + std::to_string( i / cols )
                      << '\n';
    }

    std::cout << seperator << '\n';

    std::cout << std::right
              << std::setw( left_padding )
              << '|';

    for ( auto i = 0; i < cols; ++i )
        std::cout << std::setw( col_len ) << std::to_string( i );

    std::cout << std::setw( right_padding )
              << std::left
              << " |"
              << '\n';

    std::cout.flush();
}