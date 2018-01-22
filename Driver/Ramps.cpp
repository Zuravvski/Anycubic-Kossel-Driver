/*
    Ramps.ccp - Library voor de Ramps shield
    Gemaakt door Brecht Ooms

    Modified by: Patryk Milewicz, Mateusz Wachowski, Michal Zurawski
*/

#include "Ramps.h"

//Constructor
Ramps::Ramps()
{
    pinMode(FAN_PIN, OUTPUT);

    pinMode(X_STEP_PIN, OUTPUT);
    pinMode(X_DIR_PIN, OUTPUT);
    pinMode(X_ENABLE_PIN, OUTPUT);
    pinMode(X_MIN_PIN, INPUT_PULLUP);
    pinMode(X_MAX_PIN, INPUT_PULLUP);

    pinMode(Y_STEP_PIN, OUTPUT);
    pinMode(Y_DIR_PIN, OUTPUT);
    pinMode(Y_ENABLE_PIN, OUTPUT);
    pinMode(Y_MIN_PIN, INPUT_PULLUP);
    pinMode(Y_MAX_PIN, INPUT_PULLUP);

    pinMode(Z_STEP_PIN, OUTPUT);
    pinMode(Z_DIR_PIN, OUTPUT);
    pinMode(Z_ENABLE_PIN, OUTPUT);
    pinMode(Z_MIN_PIN, INPUT_PULLUP);
    pinMode(Z_MAX_PIN, INPUT_PULLUP);
}

void Ramps::fan(bool on)
{
	if (on)
	{
		digitalWrite(FAN_PIN, HIGH);
	}
	else
	{
		digitalWrite(FAN_PIN, LOW);
	}
}

// Move motors to the home position
void Ramps::home(int delayedBy)
{
	bool allHome = false;

	motorX.stepOff();
	motorY.stepOff();
	motorZ.stepOff();

	motorX.setDir(1);
	motorY.setDir(1);
	motorZ.setDir(1);

	do
	{
		allHome = true;

		if (!digitalRead(X_MAX_PIN))
		{
			motorX.stepOn();
			allHome = false;
		}
		if (!digitalRead(Y_MAX_PIN))
		{
			motorY.stepOn();
			allHome = false;
		}
		if (!digitalRead(Z_MAX_PIN))
		{
			motorZ.stepOn();
			allHome = false;
		}

		delayMicroseconds(delayedBy);

		motorX.stepOff();
		motorY.stepOff();
		motorZ.stepOff();

	} while (!allHome);

	motorX.setDir(-1);
	motorY.setDir(-1);
	motorZ.setDir(-1);

	motorX.position = 0;
	motorY.position = 0;
	motorZ.position = 0;
}

void Ramps::moveTo(long targetX, long targetY, long targetZ, int delayedBy)
{
  	motorX.stepOff();
  	motorY.stepOff();
  	motorZ.stepOff();
  
    long deltaX = targetX - motorX.position;
    long deltaY = targetY - motorY.position;
    long deltaZ = targetZ - motorZ.position;
  
    long errorX = 0;
    long errorY = 0;
    long errorZ = 0;

    if (deltaX < 0)
    {
        motorX.setDir(-1);
        deltaX *= -1;
    }
    else
    {
        motorX.setDir(1);
    }

    if (deltaY < 0)
    {
        motorY.setDir(-1);
        deltaY *= -1;
    }
    else
    {
        motorY.setDir(1);
    }

    if (deltaZ < 0)
    {
        motorZ.setDir(-1);
        deltaZ *= -1;
    }
    else
    {
        motorZ.setDir(1);
    }
    
    if(deltaX >= deltaY && deltaX >= deltaZ)
    {
        while(motorX.position != targetX)
        {
            motorX.stepOn();

            errorY += 2*deltaY;
            errorZ += 2*deltaZ;

            if(errorY > deltaX)
            {
                motorY.stepOn();
                errorY -= 2*deltaX;
            }

            if(errorZ > deltaX)
            {
                motorZ.stepOn();
                errorZ -= 2*deltaX;
            }

            delayMicroseconds(delayedBy);

            motorX.stepOff();
            motorY.stepOff();
            motorZ.stepOff();
        }
    }
    else if(deltaZ >= deltaX && deltaZ >= deltaY)
    {
        while(motorZ.position != targetZ)
        {
            motorZ.stepOn();

            errorX += 2*deltaX;
            errorY += 2*deltaY;

            if(errorX > deltaZ)
            {
                motorX.stepOn();
                errorX -= 2*deltaZ;
            }

            if(errorY > deltaZ)
            {
                motorY.stepOn();
                errorY -= 2*deltaZ;
            }

            delayMicroseconds(delayedBy);

            motorX.stepOff();
            motorY.stepOff();
            motorZ.stepOff();
        }
    }
    else if(deltaY >= deltaX && deltaY >= deltaZ)
    {
        while(motorY.position != targetY)
        {
            motorY.stepOn();

            errorX += 2*deltaX;
            errorZ += 2*deltaZ;

            if(errorX > deltaY)
            {
                motorX.stepOn();
                errorX -= 2*deltaY;
            }

            if(errorZ > deltaY)
            {
                motorZ.stepOn();
                errorZ -= 2*deltaY;
            }

            delayMicroseconds(delayedBy);

            motorX.stepOff();
            motorY.stepOff();
            motorZ.stepOff();
        }
    }
}
