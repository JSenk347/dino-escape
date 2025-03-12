#ifndef GAME_SOUND_H
#define GAME_SOUND_H


typedef struct 
{
    int fine;
    int coarse;
    /* data */
} Note;

typedef struct
{
    Note g4 = {159,0};
    Note c5 = {119,0};
    /* data */
} Lvl_up;

typedef struct
{
    Note note;
    /* data */
} Crash;

typedef struct
{
    Note e4 = {190,0};
    Note d4_sharp = {201,0};
    Note d4 = {213,0};
    Note c4_sharp = {225,0};
    Note c4 = {239, 0};
    unsigned int num_notes;
    /* data */
} Game_Over;

/* FUNCTION DECLARATIONS */
void play_note(Note *note);
void play_sound();

#endif