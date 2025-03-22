#include "psg.h"
#include <stdio.h>

int main()
{
    Scale scale = init_scale();
    Channel channels[NUM_CHANNELS];
    init_channels(channels);

    printf("Channel A: C flat, 5th octave\nPress key\n");
    set_tone(channels[CHANNEL_A], scale.c5);
    set_volume(channels[CHANNEL_A], VOL_ON);
    enable_channel(CHANNEL_A, TRUE, FALSE);
    wait;
    printf("Channel A: C flat, 5th octave | Channel B: G flat, 4th octave\nPress key\n");
    set_tone(channels[CHANNEL_B], scale.g4);
    set_volume(channels[CHANNEL_B], VOL_ON);
    enable_channel(CHANNEL_B, TRUE, FALSE);
    wait;
    printf("Channel A: C flat, 5th octave | Channel B: G flat, 4th octave | Channel C: D flat, 4th octave\nPress key\n");
    set_tone(channels[CHANNEL_C], scale.d4);
    set_volume(channels[CHANNEL_C], VOL_ON);
    enable_channel(CHANNEL_C, TRUE, FALSE);
    wait;
    printf("Channel A: DISABLED\nPress key\n");
    enable_channel(CHANNEL_A, FALSE, FALSE);
    wait;
    printf("Channel B: DISABLED\nPress key\n");
    enable_channel(CHANNEL_B, FALSE, FALSE);
    wait;
    printf("Channel C: DISABLED\nPress key\n");
    enable_channel(CHANNEL_C, FALSE, FALSE);
    wait;
    printf("All channels ENABLED\nPress key\n");
    set_tone(channels[CHANNEL_A], scale.c5);
    set_volume(channels[CHANNEL_A], VOL_ON);
    set_tone(channels[CHANNEL_B], scale.g4);
    set_volume(channels[CHANNEL_B], VOL_ON);
    set_tone(channels[CHANNEL_C], scale.d4);
    set_volume(channels[CHANNEL_C], VOL_ON);
    enable_channel(CHANNEL_A, TRUE, FALSE);
    enable_channel(CHANNEL_B, TRUE, FALSE);
    enable_channel(CHANNEL_C, TRUE, FALSE);
    wait;
    printf("All channels DISABLED\n");
    stop_sound();
    
    return 0;
}
