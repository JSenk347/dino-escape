#include "music.h"
#include "clock.h"

int main()
{
    Scale scale;
    UINT32 prev_time, curr_time, time_passed;
    /* hold time is 70 because 70 * (1/70)th a second = 1 second*/
    Song song = {{{239, 0, 70}, {190, 0, 70}, {225, 0, 70}, {178,0, 70}}, 4, 0}; 
    Channel channels[NUM_CHANNELS];
    scale = init_scale();
    init_channels(channels);
    /*
    init_song(song_notes, scale);
    */
    
    prev_time = get_time(); 
    start_music(channels, song);
    while (!Cconis()){
        curr_time = get_time();
        time_passed = curr_time - prev_time; 
        update_music(time_passed, channels, &song);
    }
    Cnecin();
    stop_sound();

    return 0;
}