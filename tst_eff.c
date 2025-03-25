#include "effects.h"
#include <stdio.h>


int main(){
    Scale scale = init_scale();

    printf("Press to play the sound of the dino crashing into an obstacle.\n");
    wait;
    play_crash();
    printf("Press to play sound of dino passing an obstacle.\n");
    wait;
    printf("Press to exit.\n");
    play_point(scale);
    wait;
    stop_sound();

    return 0;
}