#ifndef PSG_H
#define PSG_H

#include <osbind.h>
#include "types.h"

#define ON 1
#define OFF 0
#define VOL_ON 11
#define VOL_OFF 0
#define MUSIC_CHANNEL 0
#define EFFECTS_CHANNEL 1
#define MIN_ENVELOPE_SHAPE 0
#define MAX_ENVELOPE_SHAPE 15
#define MAX_REG 15
#define MIN_REG 0
#define MAX_VOLUME 15
#define MIN_VOLUME 1
#define MAX_NOISE 31
#define MIN_NOISE 1
#define PSG_REG_ADR 0xFF8800
#define PSG_WRITE_ADR 0xFF8802
#define wait while (!Cconis()){}Cnecin(); /*a MACRO - awaits keypress till next insturction*/

/*typedef char UINT8;
typedef unsigned int bool; */

/* Sharp Notes: Indicated by uppercase; Flat Notes: indicated by lowercase*/

/* CHANNEL_A: For music; CHANNEL_B: For effects*/


typedef struct
{
    int fine;
    int coarse;
    int duration;
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
    Note f4; /*{178, 0}*/
} Scale;

typedef enum
{
    CHANNEL_A,
    CHANNEL_B,
    CHANNEL_C,
    NUM_CHANNELS
} Channel;

typedef enum
{
	A_FINE_TONE_REG,
	A_COARSE_TONE_REG,   
	B_FINE_TONE_REG,  
	B_COARSE_TONE_REG,  
	C_FINE_TONE_REG,    
	C_COARSE_TONE_REG,  
	NOISE_REG,    
	MIXER_REG,          
	A_LEVEL_REG,        
	B_LEVEL_REG,       
	C_LEVEL_REG,        
	FINE_ENVELOPE_REG,  
	COARSE_ENVELOPE_REG,
	SHAPE_ENVELOPE_REG
} Register;



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
 * @brief Loads the noise register with the defined frequency (1-31)
 * @param freq The frequency that will be played as noise (1-31)
 */
void set_noise(int tuning);

/**
 * @brief Defines the evelope shape and period (sustain (1 - 65535))
 */
void set_envelope(int shape, unsigned int sustain);

void enable_envelope(Channel channel, bool is_on);

/**
 * @brief Enables the tone and/or noise of a specified channel
 * @param channel The channel you'd like to enable
 * @param tone_on Whether you're enabling tone or not (coarse and fine)
 * @param noise_on Whether you're enabling noise or not (background noise)
 * @return none
 */
void enable_channel(Channel channel, bool tone_on, bool noise_on);

/**
 * @brief Silences all PSG sound production via the mixer and volume registers
 * @return none
 */
void stop_sound();

/*********************NON-REQUIRED FUNCTIONS*********************/

Scale init_scale();

/**
 * @brief Takes in an array of channels an initializes their registers to the appropriate values
 * @param channels A declared array of Channels
 * @return none
 */
void init_channels(Channel channels[NUM_CHANNELS]);



#endif