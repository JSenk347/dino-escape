#include "sound.h"
#include "clock.h"
#include <osbind.h>

/* WON'T COMPILE WITH -c FLAG */

int main()
{
    UINT32 curr_time, prev_time, time_passed;
    /*                g4        c5        e4        d4        D4        c4        C4   */
    Scale scale = {{159, 0}, {119, 0}, {190, 0}, {213, 0}, {201, 0}, {239, 0}, {225, 0}};
    Lvl_up lvl_up = {{159, 0}, {119, 0}, 2};
    Game_Over game_over = {{190, 0}, {201, 0}, {213, 0}, {225, 0}, {239, 0}, 5};

    Note *C4 = &scale.C4;

    prev_time = get_time();

    play_note(&scale.c4, 'A');

    Cconis();

    disable_channel('A');

    Cconis();

    play_note(&scale.C4, 'B');

    /*
    while (!Cconis()){
        curr_time = get_time();
        time_passed = curr_time - prev_time;
        

        if (time_passed > 0){
            
            if (time_passed >= 20){
                disable_channel('A');
            }
            play_note(&scale.C4, 'B');
        }
    }
    */
    

    /*
    play_note(&scale.c4, 'A');
    play_note(&scale.e4, 'B');
    play_note(&scale.d4, 'C');

    */
    
    return 0;
}