#ifndef MUSIC_H
#define MUSIC_H

#include "psg.h"
#include "clock.h"

typedef struct{
    Note notes[4];
    int hold_time;
    int curr_note;
} Song;

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
void update_music(UINT32 time_passed, Channel channels[], Song *song);

void init_song(Note notes[4], Scale scale);

#endif