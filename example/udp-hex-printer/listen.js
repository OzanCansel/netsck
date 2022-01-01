var sck  = new udp_socket()
sck.enable_stdout( false )
sck.bind( AnyIPv4 , 10000 )

print( "Listening " + sck.port() + " port" )

var c = 0

while( ( c = wait_key( 30 ) ) != Key.ESC )
{
    sck.wait_a_bit()

    if ( sck.has_datagram() )
    {
        std_out( "==================================\n" )
        std_out( "New datagram received\n" )
        std_out( "==================================\n" )

        Hex.print(
            sck.read_datagram().data
        )
    }
}