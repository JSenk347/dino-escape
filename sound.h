#ifndef SOUND_H
#define SOUND_H

#define VOL_ON 11
#define VOL_OFF 0



/* FUNCTION DECLARATIONS */
void play_note(Note *note, char channel);
void disable_channel(char channel);

#endif