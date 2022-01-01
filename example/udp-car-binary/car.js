var station = new udp_socket()
station.enable_stdout( false )
station.bind( AnyIPv4 , 10000 )

var engine_ss = 0x00
var summary   = 0x01
var speed_up  = 0x02
var move_left = 0x03
var slow_down = 0x04
var move_right= 0x05

var c      = 0
var engine = true
var pos    = 25
var h_max  = 50
var tick   = now()
var fps    = 30
var speed  = fps
var draw_if= function(){
    if ( !engine )
        return

    var delay = 1000.0 / speed
    var diff  = now() - tick

    if ( diff < delay )
        return

    tick = now()
    var visual = "|"
    for ( var i = 0; i <= h_max; ++i )
        visual += i == pos ? "|" : "="
    visual += "|" + speed + " fps"
    visual += "\n"

    std_out( visual )
}

print( "Station listening port " + station.port() )

while( ( c = wait_key( 1 ) ) != Key.ESC )
{
    station.wait_a_bit()

    if ( station.has_datagram() )
    {
        var dgram    = station.read_datagram()
        var cli_addr = dgram.sender_addr
        var cli_port = dgram.sender_port
        var command  = array( dgram.data )[ 0 ]

        if ( command == engine_ss )
        {
            engine = !engine

            if ( engine )
                print( "Engine started" )
            else
                print( "Engine stopped" )
        }
        else if ( command == summary )
        {
            station.send(
                flat( [ pos , speed , engine ] ) ,
                cli_addr ,
                cli_port
            )
        }
        else if ( command == speed_up )
        {
            speed = speed == fps * 2 ? speed : speed + 1
        }
        else if ( command == move_left )
        {
            pos = pos == 0 ? 0 : pos - 1
        }
        else if ( command == slow_down )
        {
            speed = speed == Math.round( fps / 4 ) ? speed : speed - 1   
        }
        else if ( command == move_right )
        {
            pos = pos == h_max ? h_max : pos + 1
        }
    }

    draw_if()
}

print( "Exiting..." )