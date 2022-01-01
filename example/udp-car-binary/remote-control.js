var rc = new udp_socket()
rc.enable_stdout( false )

var engine_ss    = 0x00
var summary      = 0x01
var speed_up     = 0x02
var move_left    = 0x03
var slow_down    = 0x04
var move_right   = 0x05

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
            flat( [ engine_ss ] ) ,
            station_ip ,
            station_port
        )
    else if ( c == Key.f )
        rc.send(
            flat( [ summary ] ) ,
            station_ip ,
            station_port
        )
    else if ( c == Key.w )
        rc.send(
            flat( [ speed_up ] ) ,
            station_ip ,
            station_port
        )
    else if ( c == Key.a )
        rc.send(
            flat( [ move_left ] ) ,
            station_ip ,
            station_port
        )
    else if ( c == Key.s )
        rc.send(
            flat( [ slow_down ] ) ,
            station_ip ,
            station_port
        )
    else if ( c == Key.d )
        rc.send(
            flat( [ move_right ] ) ,
            station_ip ,
            station_port
        )

    while ( rc.has_datagram() )
    {
        var result = array( rc.read_datagram().data )

        print()
        print( "Parsing [" + result + "]" )
        var pos   = result[ 0 ]
        var speed = result[ 1 ]
        var engine= result[ 2 ]

        print( "===============" )
        print( "pos    : " + pos )
        print( "speed  : " + speed )
        print( "engine : " + engine )
        print(  "===============" )
    }
}

print( "Exiting..." )