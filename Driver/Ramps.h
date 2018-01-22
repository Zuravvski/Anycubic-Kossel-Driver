/*
    Ramps.ccp - Library voor de Ramps shield
    Gemaakt door Brecht Ooms

    Modified by: Patryk Milewicz, Mateusz Wachowski, Michal Zurawski
*/

#ifndef _Ramps_h
#define _Ramps_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "PololuDriver.h"

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define FAN_PIN            9

class Ramps
{
	public: 

		Ramps();

    // Move robot to home position
		void home(int delayedBy = 1000);

		void fan(bool On);

		// Move robot to position with specified speed (The less delay you feed it with the faster it will drive)
		void moveTo(long targetX, long targetY, long targetZ, int delayedBy = 500);

		PololuStepper motorX = PololuStepper(	X_STEP_PIN, X_DIR_PIN,
												X_ENABLE_PIN);
		PololuStepper motorY = PololuStepper(	Y_STEP_PIN, Y_DIR_PIN,
												Y_ENABLE_PIN);
		PololuStepper motorZ = PololuStepper(	Z_STEP_PIN, Z_DIR_PIN,
												Z_ENABLE_PIN);

};

#endif
