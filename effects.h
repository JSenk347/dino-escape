#ifndef EFFECTS_H
#define EFFECTS_H

#include "psg.h"

#define CRASH_ENV_SHAPE 3
#define CRASH_ENV_SUSTAIN 8000
#define CRASH_NOISE 3
#define POINT_ENV_SHAPE 9
#define POINT_ENV_SUSTAIN 5888

/* REQUIRED FUNCTIONS */
void play_crash();

void play_point(Scale scale);

#endif