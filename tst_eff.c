#include "effects.h"


int main(){
    Channel channels[NUM_CHANNELS];
    Scale scale = init_scale();
    init_channels(channels);

    set_noise(1);
    set_volume(channels[CHANNEL_B], VOL_ON);
    enable_channel(CHANNEL_B, FALSE, TRUE);
    wait;
    set_tone(channels[CHANNEL_B], scale.C4);
    set_volume(channels[CHANNEL_B], VOL_ON);
    enable_channel(CHANNEL_B, TRUE, FALSE);
    wait;
    stop_sound();

    return 0;
}