/*
    Ramps.ccp - Library voor de Ramps shield
    Gemaakt door Brecht Ooms

    Modified by: Patryk Milewicz, Mateusz Wachowski, Michal Zurawski
*/

#ifndef _POLOLUDRIVER_h
#define _POLOLUDRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PololuStepper
{
	public:
		PololuStepper(int stepPin, int dirPin, int enablePin);

		void setDir(short dir);

		bool stepOn();			
		void stepOff();			

		void autoStep(long amount, int delayedBy);

		void moveTo(long targetPos, int delayedBy);

		long position = 0;

	private:
		short _dir = 1;
		bool _stepped = false;

		int _stepPin;
		int _dirPin;
		int _enablePin;

};

#endif
