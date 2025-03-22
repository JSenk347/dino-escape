#include "music.h"
#include "clock.h"
#include <stdio.h>

void start_music(Channel channels[], Song song)
{
    set_tone(channels[CHANNEL_A], song.notes[0]);
    set_volume(channels[CHANNEL_A], VOL_ON);
    enable_channel(CHANNEL_A, TRUE, FALSE);
}

void update_music(UINT32 time_passed, Channel channels[], Song *song)
{
    int i = 0;
    Note *notes = song->notes;
    if ((time_passed % (notes[song->curr_index].duration + 1)) >= notes[song->curr_index].duration)
    {
        if (song->curr_index >= song->num_notes - 1)
        {
            song->curr_index = -1;    
        }
        (song->curr_index) += 1;

        /* loop necessary to allow enough time for curr_index to update before setting tone */
        while (i <= 10)
        {
            i++;
            continue;
        }
        set_tone(channels[CHANNEL_A], notes[song -> curr_index]);
    }
    return;
}

void init_song(Note notes[4], Scale scale)
{
    notes[0] = scale.c4;
    notes[1] = scale.e4;
    notes[2] = scale.C4;
    notes[3] = scale.f4;
}
