#include "psg.h"
#include <stdio.h>

int main()
{
    /*
    Channel A = {0, 1, 8};
    Channel B = {2, 3, 9};
    Channel C = {4, 5, 10};
    */
    
    Channel channels[NUM_CHANNELS];
    channels[CHANNEL_A].fine_reg = 0;
    channels[CHANNEL_A].coarse_reg = 1;
    channels[CHANNEL_A].coarse_reg = 8;
    channels[CHANNEL_B].fine_reg = 2;
    channels[CHANNEL_B].coarse_reg = 3;
    channels[CHANNEL_B].coarse_reg = 9;
    channels[CHANNEL_C].fine_reg = 4;
    channels[CHANNEL_C].coarse_reg = 5;
    channels[CHANNEL_C].coarse_reg = 10;

    Scale scale = init_scale();
    /*
    Lvl_up lvl_up = {{159, 0}, {119, 0}, 2};
    Game_Over game_over = {{190, 0}, {201, 0}, {213, 0}, {225, 0}, {239, 0}, 5};
    */
    /*
    write_psg(A -> fine_reg, scale_ptr -> g4.fine); 
    write_psg(A -> coarse_reg, scale_ptr -> g4.coarse); 

    printf("A Fine Reg: %u\n", read_psg(A -> fine_reg)); 
    printf("A Coarse Reg: %u\n", read_psg(A -> coarse_reg)); 
    */

    
    set_tone(channels[CHANNEL_A], scale.C4);
    set_volume(channels[CHANNEL_A], VOL_ON);
    enable_channel(CHANNEL_A, TRUE, FALSE);
    wait;
    enable_channel(CHANNEL_A, FALSE, FALSE);
    
    

    
    return 0;
}
