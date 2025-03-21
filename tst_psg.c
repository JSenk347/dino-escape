#include "psg.h"
#include <stdio.h>

int main()
{
    /*                g4        c5        e4        d4        D4        c4        C4   */
    Scale scale = {{159, 0}, {119, 0}, {190, 0}, {213, 0}, {201, 0}, {239, 0}, {225, 0}};

    Channel channels[NUM_CHANNELS];
    channels[CHANNEL_A].fine_reg = 0;
    channels[CHANNEL_A].coarse_reg = 1;
    channels[CHANNEL_A].volume_reg = 8;
    channels[CHANNEL_B].fine_reg = 2;
    channels[CHANNEL_B].coarse_reg = 3;
    channels[CHANNEL_B].volume_reg = 9;
    channels[CHANNEL_C].fine_reg = 4;
    channels[CHANNEL_C].coarse_reg = 5;
    channels[CHANNEL_C].volume_reg = 10;

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
