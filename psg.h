#ifndef PSG_H
#define PSG_H

#include <osbind.h>

#define TRUE 1
#define FALSE 0
#define VOL_ON 11
#define VOL_OFF 0
#define MIXER_REG 7
#define PSG_REG_ADR 0xFF8800
#define PSG_WRITE_ADR 0xFF8802
#define wait while(!Cconis()){}Cnecin(); /*a MACRO - awaits keypress till next insturction*/

typedef char UINT8;
typedef unsigned int bool;


/* Sharp Notes: Indicated by uppercase; Flat Notes: indicated by lowercase*/

typedef struct
{
    int fine_reg;
    int coarse_reg;
    int volume_reg;
} Channel;

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

typedef enum
{
    CHANNEL_A,
    CHANNEL_B,
    CHANNEL_C,
    NUM_CHANNELS
} ChannelName;

/******************REQUIRED FUNCTIONS****************** */

/**
 * @brief Writes a specified value (0-255) to a specified register (0-15) of the PSG
 * @param reg The reg to which you'd like to write to
 * @param val The value you'd like to write to the specified register 
 * @return none
 */
void write_psg(int reg, UINT8 val);

/**
 * @brief Returns the value that exists in the specified register
 * @param reg The register from which you'd like to read from
 */
UINT8 read_psg(int reg);

/**
 * @brief Sets the note (coarse and fine tune) of a specified channel (A, B, C)
 * @param channel The channel you'd like to set the note of
 * @param note A pointer to the note you'd like to set the channel to
 * @return none
 */
void set_tone(Channel channel, Note note);

/**
 * @brief Loads the colume register for the specified channel
 * @param channel The channel you'd like to set the volume of
 * @param volume The volume you'd like to set the channel to
 * @return none
 */
void set_volume(Channel channel, int volume);

/**
 * @brief Enables the tone and/or noise of a specified channel
 * @param channel The channel you'd like to enable
 * @param tone_on Whether you're enabling tone or not (coarse and fine)
 * @param noise_on Whether you're enabling noise or not (background noise)
 * @return none
 */
void enable_channel(UINT8 channel, bool tone_on, bool noise_on);

/**
 * @brief Silences all PSG sound production via the mixer
 * @return none
 */
void stop_sound();

/*********************NON-REQUIRED FUNCTIONS*********************/


#endif