#include "music.h"
#include "clock.h"
#include <stdio.h>

int main()
{
    UINT32 prev_time, curr_time, time_passed;
    Scale scale;
    Song song;
    scale = init_scale();
    init_song(&song, scale);
    
    prev_time = get_time();
    start_music(song);

    while (!Cconis()){
        curr_time = get_time();
        time_passed = curr_time - prev_time; 
        update_music(time_passed, &song);
    }
    Cnecin();
    stop_sound();
    
    

    return 0;
}