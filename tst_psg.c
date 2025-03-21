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

    set_tone(channels[CHANNEL_A], scale.c5);
    set_volume(channels[CHANNEL_A], VOL_ON);
    enable_channel(CHANNEL_A, TRUE, FALSE);
    wait;
    enable_channel(CHANNEL_A, FALSE, FALSE);

    return 0;
}
