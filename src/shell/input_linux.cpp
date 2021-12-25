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
