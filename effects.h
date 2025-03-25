#ifndef EFFECTS_H
#define EFFECTS_H

#define CRASH_ENV_SHAPE 3
#define CRASH_ENV_SUSTAIN 8000
#define CRASH_NOISE 3
#define POINT_ENV_SHAPE 9
#define POINT_ENV_SUSTAIN 5888

#include "psg.h"
#include <osbind.h>

/* REQUIRED FUNCTIONS */
void play_crash();

void play_point(Scale scale);

#endif