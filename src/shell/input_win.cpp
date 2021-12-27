#include "input.hpp"
#include <iostream>
#include <algorithm>
#include <QtGlobal>
#include <windows.h>

void enable_stdin_echo( bool enable )
{
    HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE );
    DWORD mode;

    GetConsoleMode( hStdin , &mode );

    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode( hStdin, mode );
}

void enable_line_input( bool enable )
{
    HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE ); 
    DWORD mode;

    GetConsoleMode( hStdin , &mode );

    if( enable )
        mode |= ENABLE_LINE_INPUT;
    else
        mode &= ~ENABLE_LINE_INPUT;

    SetConsoleMode( hStdin, mode );
}

int wait_key( int timeout )
{
    enable_stdin_echo( false );
    enable_line_input( false );

    DWORD fdwOldMode;
    HANDLE hStdIn = GetStdHandle( STD_INPUT_HANDLE );
    GetConsoleMode( hStdIn , &fdwOldMode );
    DWORD fdwMode = fdwOldMode ^ ENABLE_MOUSE_INPUT ^ ENABLE_WINDOW_INPUT;
    SetConsoleMode( hStdIn , fdwMode );
    FlushConsoleInputBuffer( hStdIn );

    int key { -1 };

    while ( WaitForSingleObject( hStdIn , timeout ) == WAIT_OBJECT_0 )
    {
        INPUT_RECORD records[512];
        DWORD n_records;
        ReadConsoleInput( hStdIn , records , 512 , &n_records );

        auto key_event = std::find_if(
            std::begin( records ) ,
            std::begin( records ) + n_records ,
            []( const INPUT_RECORD& rec ){
                return rec.EventType == KEY_EVENT;
            }
        );

        auto found { key_event != std::begin( records ) + n_records };

        if ( found )
        {
            if ( key_event->Event.KeyEvent.bKeyDown )
            {
                key = key_event->Event.KeyEvent.uChar.AsciiChar;

                break;
            }
        }
        else
        {
            break;
        }
    }

    SetConsoleMode( hStdIn , fdwOldMode );
    enable_stdin_echo( true );
    enable_line_input( true );

    return key;
}

void fill_keys( QJSValue& keys )
{   }