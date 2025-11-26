/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "init.h"
#include "rotary_calculator.h"
#include "rotary_display.h"
#include "rotary_input.h"
#include "rotary_states.h"
#include "timer.h"
#include <stdint.h>
#include <timer.h>
#include <lcd.h>
#include "rotary_led.h"

#define PHASE_MASK 0x3
#define PHASE_WIDTH 2
#define MS_PER_US 1000.0
#define S_PER_MS 1000.0
#define MS_PER_TICK (TICKS_PER_US * MS_PER_US)
#define S_PER_TICK (MS_PER_TICK * S_PER_MS)
#define MAX_DEGREES 1200.0
#define DEGREE_PER_MOVEMENT (360.0 / MAX_DEGREES)

int main(void) {
	uint32_t lastUpdate = 0;
	double angle = 0.0;
	double lastAngle = 0.0;
	double anglePerSec = 0;
	int phaseCounter = 0;
	bool errorState = false;

	initITSboard();
	initDisplay();
	initTimer();

	uint32_t lastPhase = readInput();
	while(1) {	
		uint32_t phase = readInput();
		uint32_t timestamp = getTimeStamp();

		if(errorState)
		{
			if(buttonS6_pressed())
			{
				lastPhase = readInput();
				clearErrorLED();
				phaseCounter = 0;
				errorState = false;
			}

			continue;
		}
		
		// process signal
		int state = rotary_determineState(lastPhase, phase);
		lastPhase = phase;

		// read signal
		uint32_t timeSinceUpdate = timestamp - lastUpdate;
		double timeInSeconds = timeSinceUpdate / S_PER_TICK;
		if ((timeInSeconds >= 0.25 && state != STATE_NOCHANGE) || timeInSeconds > 0.5) {
			double angleDiff = angle - lastAngle;
			anglePerSec = angleDiff / timeInSeconds;
			lastAngle = angle;
			lastUpdate = timestamp;
		}

		// control actuators
		switch (state) {
			case STATE_FORWARD:
				phaseCounter++;
				break;
			case STATE_BACKWARDS:
				phaseCounter--;
				break;
			case STATE_NOCHANGE:
				// no change
				break;
			case STATE_ERROR:
				setErrorLED();
				errorState = true;
				break;
		}

		angle = phaseCounter * DEGREE_PER_MOVEMENT;

		updateDisplay(angle, anglePerSec);
		setLEDCounter(phaseCounter);
		setLEDDirection(state);
	}
}

// EOF
