#ifndef GAME_SND_H
#define GAME_SND_H

#define VOL_ON 11

/* Sharp Notes: Indicated by uppercase; Flat Notes: indicated by lowercase*/

typedef struct
{
    int fine;
    int coarse;
} Note;

typedef struct
{
    Note g4; /*{159,0}*/
    Note c5; /*{119,0}*/
    Note e4; /*{190,0}*/
    Note d4; /*{213,0}*/
    Note D4; /*{201,0}*/
    Note c4; /*{239,0}*/
    Note C4; /*{225,0}*/
} Scale;

typedef struct
{
    Note g4;
    Note c5;
    unsigned int num_notes;
    /* notes = [g4 = {159, 0}, c5 = {119,0}] */
} Lvl_up;

typedef struct
{
    Note note;
    /* data */
} Crash;

typedef struct
{
    Note e4;
    Note D4;
    Note d4;
    Note C4;
    Note c4;
    unsigned int num_notes;
} Game_Over;

/* FUNCTION DECLARATIONS */
void play_note();

#endif