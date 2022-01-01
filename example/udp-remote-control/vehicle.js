var station = new udp_socket()
station.enable_stdout( false )
station.bind( AnyIPv4 , 10000 )

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

    stdout( visual )
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
        var command  = dgram.data_utf8

        if ( command == "ss_engine" )
        {
            engine = !engine

            if ( engine )
                print( "Engine started" )
            else
                print( "Engine stopped" )
        }
        else if ( command == "summary" )
        {
            station.send(
                "\n===============\n" +
                "pos    : " + pos + "\n" +
                "speed  : " + speed + "\n" +
                "engine : " + engine + "\n" +
                "===============\n" ,
                cli_addr ,
                cli_port
            )
        }
        else if ( command == "speed_up" )
        {
            speed = speed == fps * 2 ? speed : speed + 1
        }
        else if ( command == "move_left" )
        {
            pos = pos == 0 ? 0 : pos - 1
        }
        else if ( command == "slow_down" )
        {
            speed = speed == Math.round( fps / 4 ) ? speed : speed - 1   
        }
        else if ( command == "move_right" )
        {
            pos = pos == h_max ? h_max : pos + 1
        }
    }

    draw_if()
}

print( "Exiting..." )