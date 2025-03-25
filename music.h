#ifndef MUSIC_H
#define MUSIC_H

#include "psg.h"
#include "clock.h"

typedef struct{
    Note notes[4];
    int num_notes;
    int curr_index;
} Song;

typedef enum{
    NOTE_1,
    NOTE_2,
    NOTE_3,
    NOTE_4,
    NUM_NOTES
} NoteIndex;

/**
 * @brief Begins playing the synchronous song by loading the first note of
 * the song into the PSG
 * @return none
 */
void start_music();

/**
 * @brief Advances to the next note if necessary, based on the amount of
 * time that has passed since the initial call
 * @param time_passed The amount of time that has passed since the first
 * call
 * @return none
 */
void update_music(UINT32 time_passed, Song *song);

void init_song(Song *song, Scale scale);

#endif