#include "clock.h"
#include <osbind.h>

typedef unsigned long UINT32;

UINT32 get_time() {
    long *timer = (long *)0x462;
    long time_now;
    long old_ssp;

    old_ssp = Super(0); /* Enter privileged mode */
    time_now = *timer;
    Super(old_ssp);     /* Exit privileged mode */
    return time_now;
}