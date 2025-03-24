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
    wait;
    set_envelope(3, 3);
    set_tone(channels[CHANNEL_B], scale.C4);
    /*write_psg(channels[CHANNEL_B].volume_reg, 0x14);*/
    toggle_envelope(channels[CHANNEL_B]);
    /*set_volume(channels[CHANNEL_B], VOL_ON);*/
    enable_channel(CHANNEL_B, FALSE, TRUE);
    wait;
    toggle_envelope(channels[CHANNEL_B]);
    set_envelope(3, 3);
    wait;
    stop_sound();

    return 0;
}