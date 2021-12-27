#pragma once

#include <QJSValue>

void enable_stdin_echo( bool enable = true );
void enable_line_input( bool enable = true );
int wait_key( int timeout );
void fill_keys( QJSValue& keys );