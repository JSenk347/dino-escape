#include "music.h"
#include "clock.h"


void start_music(Channel channels[], Note song[]){
    set_tone(channels[CHANNEL_A], song[0]);
    set_volume(channels[CHANNEL_A], VOL_ON);
    enable_channel(CHANNEL_A, TRUE, FALSE);
}


void update_music(UINT32 time_passed, Channel channels[], Song *song){
    if ((time_passed % 71)  >= song -> hold_time){
        if (song ->curr_note == 3){
            song ->curr_note = 0;
        }
        song->curr_note += 1;
        set_tone(channels[CHANNEL_A], song -> notes[song -> curr_note]);
    }
}

void init_song(Note notes[4], Scale scale){
    notes[0] = scale.c4;
    notes[1] = scale.e4;
    notes[2] = scale.C4;
    notes[3] = scale.f4;
}
