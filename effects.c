#include "effects.h"
#include "psg.h"
#include "clock.h"
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
	Volume Registers (8, 9, 10):
		- X X X M V V V V
		- X = Not used; M = Mode (1 - Envelope On, 0 - Envelope Off); V = Volume
	*/

void play_crash(){
	enable_channel(EFFECTS_CHANNEL, OFF, OFF);
	set_noise(CRASH_NOISE);
	set_volume(EFFECTS_CHANNEL, VOL_ON);
	enable_channel(EFFECTS_CHANNEL, OFF, ON);
	enable_envelope(EFFECTS_CHANNEL, ON);
	set_envelope(CRASH_ENV_SHAPE, CRASH_ENV_SUSTAIN);
}

void play_point(Scale scale){
	enable_channel(EFFECTS_CHANNEL, OFF, OFF);
	set_tone(EFFECTS_CHANNEL, scale.f4);
	set_volume(EFFECTS_CHANNEL, VOL_ON);
    enable_channel(EFFECTS_CHANNEL, ON, OFF);
    enable_envelope(EFFECTS_CHANNEL, ON);
    set_envelope(POINT_ENV_SHAPE, POINT_ENV_SUSTAIN);
}


