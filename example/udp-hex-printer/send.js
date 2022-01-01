var sck = new udp_socket()
sck.enable_stdout( false )

var c = 0

std_out( "====================================\n" )
std_out( "Enter 'exit' or 'quit' to exit.\n" )

while( ( c = wait_key( 50 ) ) != Key.ESC )
{
    std_out( "Enter hex message ( i.e '0f f1 2d de') : " )
    var line = read_line()

    if ( line == "exit" || line == "quit" )
        break;

    sck.send(
        Hex.from( line ) ,
        LocalHost ,
        10000
    )
}