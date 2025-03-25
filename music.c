#include "music.h"
#include "clock.h"
#include <stdio.h>
/*******************************************************************************
    PURPOSE: Start playing music
    INPUT:	- Song - song to play
    OUTPUT: - N/A
*******************************************************************************/
void start_music(Song song)
{
    set_tone(MUSIC_CHANNEL, song.notes[0]); /* MAKE SURE ALL NOTES ARE THERE */
    set_volume(MUSIC_CHANNEL, VOL_ON);
    enable_channel(MUSIC_CHANNEL, ON, OFF);
}
/*******************************************************************************
    PURPOSE: Update the note being played
    INPUT:	- Song - song being played
            - time_passed - time passed since last update
    OUTPUT: - N/A
*******************************************************************************/
void update_music(UINT32 time_passed, Song *song)
{
    int i = 0;
    Note *notes = song->notes;
    int *curr_index = &song -> curr_index;
    int num_notes = song -> num_notes;
    int *timer = &song -> timer;
    
    
    if ((time_passed % (notes[*curr_index].duration + 1)) >= notes[*curr_index].duration)
    {
        if (*curr_index >= num_notes - 1)
        {
            *curr_index = -1;    
        }
        (*curr_index) += 1;
        /*loop necessary to allow enough time for curr_index to update before setting tone */
        set_tone(MUSIC_CHANNEL, notes[*curr_index]);

    }
    
    
    
    return;
}
/*******************************************************************************
    PURPOSE: Initialize the song to be played
    INPUT:	- Song - song being played
            - Scale - scale to play the song in
    OUTPUT: - N/A
*******************************************************************************/
void init_song(Song *song, Scale scale)
{
    song->notes[0] = scale.c4;
    song -> notes[0].duration = 10;
    song->notes[1] = scale.e4;
    song -> notes[1].duration = 10;
    song->notes[2] = scale.C4;
    song -> notes[2].duration = 10;
    song->notes[3] = scale.f4;
    song -> notes[3].duration = 10;
    song->num_notes = 4;
    song->curr_index = 0;
}
