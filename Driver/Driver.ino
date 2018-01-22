/*
    Driver.ccp - A Anycubic Kossel 3D Printer Driver
    designed to move the printer according to the
    external data received from Matlab over serial port.

    A driver uses RAMPS library adaptation by momostein
    (https://github.com/momostein/Ramps)

    Authors: Patryk Milewicz, Mateusz Wachowski, Michal Zurawski
    https://github.com/Zuravvski/Anycubic-Kossel-Driver
*/

#include "Ramps.h"
#include "Position.h"

Ramps ramps;

void setup() 
{
  Serial.begin(57600);

    // Find origin
    ramps.home(100);
    delay(1000);
    // Move to a specified position
    ramps.moveTo(-13000, -13000, -13000, 50); 
    // Notify matlab
    Serial.print('k');
}

Position ReadPosition(bool * readFlag)
{
    Position position;
    
    while(Serial.available())
    {
      buff = Serial.readString();
      if(buff.length() > 0)
      {
          int x, y, z;
          sscanf(buff.c_str(), "x %d y %d z %d", &x, &y, &z);
          position._x = x;
          position._y = y;
          position._z = z;
          *readFlag = true;
      }
    }
    return position;
}

void runMotor(long x, long y, long z, int delayedBy = 1000)
{
    if(digitalRead(X_MAX_PIN) != 1 && x > 0)   
      digitalWrite(X_STEP_PIN, LOW);
    if(digitalRead(Y_MAX_PIN) != 1 && y > 0)  
      digitalWrite(Y_STEP_PIN, LOW);
    if(digitalRead(Z_MAX_PIN) != 1 && z > 0)  
      digitalWrite(Z_STEP_PIN, LOW);
      
    delayMicroseconds(delayedBy);
    
    digitalWrite(X_STEP_PIN,HIGH);
    digitalWrite(Y_STEP_PIN,HIGH);
    digitalWrite(Z_STEP_PIN,HIGH);
}

void loop() 
{
    bool readFlag = false;
    Position position = ReadPosition(&readFlag);
  
    long ax = abs(position._x);
    long ay = abs(position._y);
    long az = abs(position._z);
    long total =  ax + ay + az;
  
    Serial.println(ax);
    Serial.println(ay);
    Serial.println(az);
    
    if(readFlag) 
    {
        ramps.motorX.setDir(position._x);
        ramps.motorY.setDir(position._y);
        ramps.motorZ.setDir(position._z);
        
        while(total-- > 0)
        {
          runMotor(ax--, ay--, az--, 100);
        }
    
        readFlag = false;
        Serial.print('k');
    }
}


