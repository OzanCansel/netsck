var rc = new udp_socket()
rc.enable_stdout( false )

var station_ip   = LocalHost
var station_port = 10000

var help_fn = function(){
    print( "Press 'ESC' to quit" )
    print( "Press 'h' to show help" )
    print( "Press 'e' to start/stop engine" )
    print( "Press 'f' to show summary" )
    print( "Press 'w' to speed up" )
    print( "Press 'a' to move left" )
    print( "Press 's' to slow down" )
    print( "Press 'd' to move right" )
}

var send    = function( command ){
    print( command )

    rc.send(
        command ,
        station_ip ,
        station_port
    )
}

help_fn()

var c = 0

while( ( c = wait_key( 30 ) ) != Key.ESC )
{
    rc.wait_a_bit()

    if ( c == Key.h )
        help_fn()
    else if ( c == Key.e )
        send( "ss_engine" , )
    else if ( c == Key.f )
        send( "summary" )
    else if ( c == Key.w )
        send( "speed_up" )
    else if ( c == Key.a )
        send( "move_left" )
    else if ( c == Key.s )
        send( "slow_down" )
    else if ( c == Key.d )
        send( "move_right" )

    while ( rc.has_datagram() )
        print( rc.read_datagram().data_utf8 )
}

print( "Exiting..." )