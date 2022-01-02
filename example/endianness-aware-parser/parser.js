var be_raw_float  = [ 0x44 , 0x9a , 0x50 , 0xc3 ]                             // 1234.5238
var le_raw_float  = [ 0xc3 , 0x50 , 0x9a , 0x44 ]                             // 1234.5238
var be_raw_double = [ 0x40 , 0x2c , 0xc5 , 0x7c , 0x9e , 0xd8 , 0xfb , 0x15 ] // 14.3857164039487
var le_raw_double = [ 0x15 , 0xfb , 0xd8 , 0x9e , 0x7c , 0xc5 , 0x2c , 0x40 ] // 14.3857164039487
var be_raw_int64  = [ 0x00 , 0x04 , 0x62 , 0xd5 , 0x3c , 0x9b , 0xaf , 0x07 ] // 1234567891234567
var le_raw_int64  = [ 0x07 , 0xaf , 0x9b , 0x3c , 0xd5 , 0x62 , 0x04 , 0x00 ] // 1234567891234567
var be_raw_int32  = [ 0x07 , 0x5b , 0xcd , 0x15 ]                             // 123456789
var le_raw_int32  = [ 0x15 , 0xcd , 0x5b , 0x07 ]                             // 123456789
var be_raw_uint32 = [ 0xfc , 0x7b , 0xbb , 0x35 ]                             // 4235967285
var le_raw_uint32 = [ 0x35 , 0xbb , 0x7b , 0xfc ]                             // 4235967285
var be_raw_int16  = [ 0x7d , 0x90 ]                                           // 32144
var le_raw_int16  = [ 0x90 , 0x7d ]                                           // 32144
var be_raw_uint16 = [ 0xf6 , 0x30 ]                                           // 63024
var le_raw_uint16 = [ 0x30 , 0xf6 ]                                           // 63024

print( "Parse as big endian" )
print( "1234.5238        == " + befloat( be_raw_float ) )
print( "14.3857164039487 == " + bedouble( be_raw_double ) )
print( "1234567891234567 == " + beint64( be_raw_int64 ) )
print( "123456789        == " + beint32( be_raw_int32 ) )
print( "32144            == " + beint16( be_raw_int16 ) )

print()
print( "Parse as little endian" )
print( "1234.5238        == " + lefloat( le_raw_float ) )
print( "14.3857164039487 == " + ledouble( le_raw_double ) )
print( "1234567891234567 == " + leint64( le_raw_int64 ) )
print( "123456789        == " + leint32( le_raw_int32 ) )
print( "32144            == " + leint16( le_raw_int16 ) )

var data = [ 0x01 , 0x02 , 0xf6 , 0x30 , 0x04 , 0x07 , 0x5b , 0xcd , 0x15 ]
//         |     258     |    63024    |  4   |         123456789         |

print()
print( "Parse slices of the array" )
print( beint16( data.slice( 0 , 2 ) ) )
print( beuint16( data.slice( 2 , 4 ) ) )
print( data.slice( 4 , 5 )[ 0 ] )
print( beint32( data.slice( 5 , 9 ) ) )

var concatenated = [ ...be_raw_uint16 , ...be_raw_int32 , ...be_raw_float ]

print()
print( "Concetanated byte array : " )
Hex.print( flat( concatenated ) )