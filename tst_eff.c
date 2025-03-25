#include "effects.h"
#include <stdio.h>


int main(){
    Channel channels[NUM_CHANNELS];
    Scale scale = init_scale();
    init_channels(channels);


    set_volume(channels[CHANNEL_A], VOL_ON);
    printf("Press to play the sound of the dino crashing into an obstacle.\n");
    wait;
    play_crash(channels[CHANNEL_A]);
     
    printf("Press to play sound of dino passing an obstacle.\n");
    wait;
    printf("Press to exit.\n");
    play_point(channels[CHANNEL_A]);
    
    wait;
    stop_sound();

    /*
    set_tone(channels[CHANNEL_A], scale.C4);
    enable_channel(CHANNEL_A, FALSE, FALSE);
    toggle_envelope(channels[CHANNEL_A]);
    set_envelope(9, 0x1700);
    */
    
    /*
    set_tone(channels[CHANNEL_A], scale.C4);
    set_volume(channels[CHANNEL_A], VOL_ON);
    enable_channel(CHANNEL_A, TRUE, FALSE);
    wait;
    set_noise(1);
    enable_channel(CHANNEL_A, TRUE, TRUE);
    toggle_envelope(channels[CHANNEL_A]);
    set_envelope(3, 8000);
    wait;
    stop_sound();

    */
    

    return 0;
}