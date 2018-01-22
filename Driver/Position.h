/*
    Position.h - A Anycubic Kossel 3D Printer Driver
    designed to move the printer according to the
    external data received from Matlab over serial port.

    A driver uses RAMPS library adaptation by momostein
    (https://github.com/momostein/Ramps)

    Authors: Patryk Milewicz, Mateusz Wachowski, Michal Zurawski
    https://github.com/Zuravvski/Anycubic-Kossel-Driver
*/

struct Position 
{
  Position(long x = 0, long y = 0, long z = 0)
  {
    _x = x;
    _y = y;
    _z = z;
  }
  
  long _x;
  long _y;
  long _z;  
};

