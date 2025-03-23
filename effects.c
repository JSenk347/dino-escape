#include "effects.h"
#include "psg.h"
#include <osbind.h>

/**
	FILE PURPOSE: The file must be used for the creation of sound effects generated
	during gameplay.
	REQUIREMENTS:
		- Sound effect triggered by asynchronus event
		- Sound effect triggered by synchronous event
	ALSO:
		- events.c must also be updated to play these sounds each time the event occurs
		- noise and evelope must be used
 */

/*
REGISTER SELECTIONS:
	A:
		- 0: fine tune
		- 1: coarse tune
		- 8: volume
	B:
		- 2: fine tune
		- 3: coarse tune
		- 9: volume
	C:
		- 4: fine tune
		- 5: coarse tune
		- 10: volume
	Mixer (R7):
		- Controls enabling/diabling tone and noise for ALL channels at once
		- 1 = OFF; 0 = ON
		BIT PATTERN:
			| IO | NOISE |  TONE |
		     0  0  C B A   C B A
		EG:
			- 1101 1011; Only channel C's noise and tone is on
	Noise (R6):
		- 	5 Bit frequency must be loaded into the noise register

	Evelope Shape (R13):
		- See page 20 of the YM2149 Manual
	Envelope Period/Sustain (R11 and R12):
		- See page 19 of YM2149 Manual
	*/

void play_crash(){
	
}


