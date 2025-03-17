#include "game_snd.h"
#include "clock.h"
#include <osbind.h>

/* WON'T COMPILE WITH -c FLAG */

int main()
{
    /*                g4        c5        e4        d4        D4        c4        C4   */
    Scale scale = {{159, 0}, {119, 0}, {190, 0}, {213, 0}, {201, 0}, {239, 0}, {225, 0}};
    Lvl_up lvl_up = {{159, 0}, {119, 0}, 2};
    Game_Over game_over = {{190, 0}, {201, 0}, {213, 0}, {225, 0}, {239, 0}, 5};
    ULONG32 curr_time, prev_time, time_elapsed;


    Note *note = &scale.C4;

    curr_time = get_time();
    while (!Cconin())
    {
        time_elapsed = curr_time - prev_time;
        if (time_elapsed > 0){
            play_note(note);
        }
        prev_time = curr_time;
    }
    

    

    

    return 0;
}