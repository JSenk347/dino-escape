#include "music.h"
#include "clock.h"

int main()
{
    UINT32 prev_time, curr_time, time_passed;
    Scale scale = init_scale();
    Note song_notes[4] = {{239, 0}, {190, 0}, {225, 0}, {178,0}};
    Song song = {{{239, 0}, {190, 0}, {225, 0}, {178,0}}, 70, 0};
    Channel channels[NUM_CHANNELS];
    init_channels(channels);
    /*
    init_song(song_notes, scale);
    */
    


    prev_time = get_time(); 
    start_music(channels, song.notes);
    while (!Cconis()){
        curr_time = get_time();
        time_passed = curr_time - prev_time; 
        update_music(time_passed, channels, &song);
    }
    Cnecin();
    stop_sound();

    return 0;
}