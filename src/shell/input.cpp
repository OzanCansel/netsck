#include "input.hpp"
#include <iostream>
#include <cstdio>

#ifdef Q_OS_WIN
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <poll.h>
#endif

void enable_stdin_echo( bool enable )
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE );
    DWORD mode;

    GetConsoleMode( hStdin , &mode );

    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode( hStdin, mode );
#else
    termios tty;

    tcgetattr( STDIN_FILENO , &tty );

    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    tcsetattr( STDIN_FILENO , TCSANOW , &tty );
#endif
}

void enable_line_input( bool enable )
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE ); 
    DWORD mode;
    GetConsoleMode( hStdin , &mode );

    if( enable )
        mode |= ENABLE_LINE_INPUT;
    else
        mode &= ~ENABLE_LINE_INPUT;

    SetConsoleMode( hStdin, mode );

#else
    termios tty;
    tcgetattr( STDIN_FILENO , &tty );

    if( enable )
        tty.c_lflag |= ICANON;
    else
        tty.c_lflag &= ~ICANON;

    tcsetattr( STDIN_FILENO , TCSANOW , &tty );
#endif
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