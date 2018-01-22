/*
    Ramps.ccp - Library voor de Ramps shield
    Gemaakt door Brecht Ooms

    Modified by: Patryk Milewicz, Mateusz Wachowski, Michal Zurawski
*/

#include "PololuDriver.h"
#include "Arduino.h"

PololuStepper::PololuStepper(int stepPin, int dirPin, int enablePin)
{
	_stepPin = stepPin;
	_dirPin = dirPin;
	_enablePin = enablePin;

	pinMode(_stepPin, OUTPUT);
	pinMode(_dirPin, OUTPUT);
	pinMode(_enablePin, OUTPUT);

	digitalWrite(_enablePin, LOW);
}

void PololuStepper::setDir(short dir)
{
  	if (dir > 0)
  	{
    	_dir = 1;
    	digitalWrite(_dirPin, LOW);
  	}
  	else if (dir < 0)
  	{
    	_dir = -1;
    	digitalWrite(_dirPin, HIGH);
  	}
}

bool PololuStepper::stepOn()
{
	if (!_stepped)
	{
		position += _dir;
		digitalWrite(_stepPin, HIGH);
		_stepped = true;

		return true;
	}
	else
	{
		return false;
	}
}

void PololuStepper::stepOff()
{
	if (_stepped)
	{
		digitalWrite(_stepPin, LOW);
		_stepped = false;
	}
}

void PololuStepper::autoStep(long amount, int delayedBy)
{
	setDir(constrain(amount, -1, 1));

	if (_stepped)
	{
		stepOff();
	}

	while (!(amount == 0))
	{
		stepOn();
		delayMicroseconds(delayedBy);
		stepOff();

		amount -= _dir;
	}
}

void PololuStepper::moveTo(long targetPos, int delayedBy)
{
	autoStep(targetPos - position, delayedBy);
}
