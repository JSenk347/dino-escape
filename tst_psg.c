#include "psg.h"
#include <stdio.h>

int main()
{
    Scale scale = init_scale();

    printf("Channel A: C, 5th octave\nPress key\n");
    set_tone(CHANNEL_A, scale.c4);
    set_volume(CHANNEL_A, VOL_ON);
    enable_channel(CHANNEL_A, ON, OFF);
    wait;
    printf("Channel A: C, 5th octave | Channel B: G, 4th octave\nPress key\n");
    set_tone(CHANNEL_B, scale.g4);
    set_volume(CHANNEL_B, VOL_ON);
    enable_channel(CHANNEL_B, ON, OFF);
    wait;
    printf("Channel A: C, 5th octave | Channel B: G, 4th octave | Channel C: D, 4th octave\nPress key\n");
    set_tone(CHANNEL_C, scale.d4);
    set_volume(CHANNEL_C, VOL_ON);
    enable_channel(CHANNEL_C, ON, OFF);
    wait;
    printf("Channel A DISABLED\nPress key\n");
    enable_channel(CHANNEL_A, OFF, OFF);
    wait;
    printf("Channel B DISABLED\nPress key\n");
    enable_channel(CHANNEL_B, OFF, OFF);
    wait;
    printf("Channel C DISABLED\nPress key\n");
    enable_channel(CHANNEL_C, OFF, OFF);
    wait;
    printf("All channels ENABLED\nPress key\n");
    enable_channel(CHANNEL_A, ON, OFF);
    enable_channel(CHANNEL_B, ON, OFF);
    enable_channel(CHANNEL_C, ON, OFF);
    wait;
    printf("All channels DISABLED\n");
    stop_sound();

    return 0;
}
