#include "input.hpp"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <termios.h>
#include <unistd.h>
#include <poll.h>

void enable_stdin_echo( bool enable )
{
    termios tty;

    tcgetattr( STDIN_FILENO , &tty );

    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    tcsetattr( STDIN_FILENO , TCSANOW , &tty );
}

void enable_line_input( bool enable )
{
    termios tty;
    tcgetattr( STDIN_FILENO , &tty );

    if( enable )
        tty.c_lflag |= ICANON;
    else
        tty.c_lflag &= ~ICANON;

    tcsetattr( STDIN_FILENO , TCSANOW , &tty );
}

int wait_key( int timeout )
{
    enable_stdin_echo( false );
    enable_line_input( false );

    pollfd fd[ 1 ] = {
        STDIN_FILENO ,
        POLLIN ,
        0
    };

    int key { -1 };

    if ( poll( fd , 1 , timeout ) > 0 )
        key = std::getchar();

    enable_stdin_echo( true );
    enable_line_input( true );

    return key;
}

void fill_keys( QJSValue& keys )
{
    keys.setProperty( "TAB"       , 9   );
    keys.setProperty( "RETURN"    , 10  );
    keys.setProperty( "ESC"       , 27  );
    keys.setProperty( "Space"     , 32  );
    keys.setProperty( "Exclam"    , 33  );
    keys.setProperty( "D0"        , 48  );
    keys.setProperty( "D1"        , 49  );
    keys.setProperty( "D2"        , 50  );
    keys.setProperty( "D3"        , 51  );
    keys.setProperty( "D4"        , 52  );
    keys.setProperty( "D5"        , 53  );
    keys.setProperty( "D6"        , 54  );
    keys.setProperty( "D7"        , 55  );
    keys.setProperty( "D8"        , 56  );
    keys.setProperty( "D9"        , 57  );
    keys.setProperty( "Colon"     , 58  );
    keys.setProperty( "SemiColon" , 59  );
    keys.setProperty( "Less"      , 60  );
    keys.setProperty( "Equal"     , 61  );
    keys.setProperty( "Greater"   , 62  );
    keys.setProperty( "Question"  , 63  );
    keys.setProperty( "At"        , 64  );
    keys.setProperty( "A"         , 65  );
    keys.setProperty( "B"         , 66  );
    keys.setProperty( "C"         , 67  );
    keys.setProperty( "D"         , 68  );
    keys.setProperty( "E"         , 69  );
    keys.setProperty( "F"         , 70  );
    keys.setProperty( "G"         , 71  );
    keys.setProperty( "H"         , 72  );
    keys.setProperty( "J"         , 74  );
    keys.setProperty( "K"         , 75  );
    keys.setProperty( "L"         , 76  );
    keys.setProperty( "M"         , 77  );
    keys.setProperty( "N"         , 78  );
    keys.setProperty( "O"         , 79  );
    keys.setProperty( "P"         , 80  );
    keys.setProperty( "Q"         , 81  );
    keys.setProperty( "R"         , 82  );
    keys.setProperty( "S"         , 83  );
    keys.setProperty( "T"         , 84  );
    keys.setProperty( "U"         , 85  );
    keys.setProperty( "V"         , 86  );
    keys.setProperty( "W"         , 87  );
    keys.setProperty( "X"         , 88  );
    keys.setProperty( "Y"         , 89  );
    keys.setProperty( "Z"         , 90  );
    keys.setProperty( "Underscore", 95  );
    keys.setProperty( "a"         , 97  );
    keys.setProperty( "b"         , 98  );
    keys.setProperty( "c"         , 99  );
    keys.setProperty( "d"         , 100 );
    keys.setProperty( "e"         , 101 );
    keys.setProperty( "f"         , 102 );
    keys.setProperty( "g"         , 103 );
    keys.setProperty( "h"         , 104 );
    keys.setProperty( "j"         , 106 );
    keys.setProperty( "k"         , 107 );
    keys.setProperty( "l"         , 108 );
    keys.setProperty( "m"         , 109 );
    keys.setProperty( "n"         , 110 );
    keys.setProperty( "o"         , 111 );
    keys.setProperty( "p"         , 112 );
    keys.setProperty( "q"         , 113 );
    keys.setProperty( "r"         , 114 );
    keys.setProperty( "s"         , 115 );
    keys.setProperty( "t"         , 116 );
    keys.setProperty( "y"         , 117 );
    keys.setProperty( "v"         , 118 );
    keys.setProperty( "w"         , 119 );
    keys.setProperty( "x"         , 120 );
    keys.setProperty( "y"         , 121 );
    keys.setProperty( "z"         , 122 );
    keys.setProperty( "Tilda"     , 126 );
    keys.setProperty( "Backspace" , 127 );
}