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

help_fn()

var c = 0

while( ( c = wait_key( 30 ) ) != Key.ESC )
{
    rc.wait_a_bit()

    if ( c == Key.h )
        help_fn()
    else if ( c == Key.e )
        rc.send(
            "ss_engine" ,
            station_ip ,
            station_port
        )
    else if ( c == Key.f )
        rc.send(
            "summary" ,
            station_ip ,
            station_port
        )
    else if ( c == Key.w )
        rc.send(
            "speed_up" ,
            station_ip ,
            station_port
        )
    else if ( c == Key.a )
        rc.send(
            "move_left" ,
            station_ip ,
            station_port
        )
    else if ( c == Key.s )
        rc.send(
            "slow_down" ,
            station_ip ,
            station_port
        )
    else if ( c == Key.d )
        rc.send(
            "move_right" ,
            station_ip ,
            station_port
        )

    while ( rc.has_datagram() )
        print( rc.read_datagram().data_utf8 )
}

print( "Exiting..." )