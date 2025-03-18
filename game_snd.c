#include "game_snd.h"
#include <osbind.h>

/*
REGISTER SELECTIONS:
	A:
		- 0: fine tune
		- 1: coarse tune
		- 8: volume
	B:
		- 2: fine tune
		- 3: coarse tune
		- 9: volume
	C:
		- 4: fine tune
		- 5: coarse tune
		- 10: volume
	Mixer (R7):
		Controls enabling/diabling tone and noise for ALL channels at once
	*/

void play_note(Note *note, char channel)
{
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write = 0xFF8802;
	long old_ssp = Super(0);

	int fine_reg, coarse_reg, volume_reg;
	unsigned char mixer = 0x3F;

	switch (channel)
	{
	case 'A':
		fine_reg = 0;
		coarse_reg = 1;
		volume_reg = 8;
		mixer &= ~0x01; /* enables A */
		break;
	case 'B':
		fine_reg = 2;
		coarse_reg = 3;
		volume_reg = 9;
		mixer &= ~0x02; /* enables B */
		break;
	case 'C':
		fine_reg = 4;
		coarse_reg = 5;
		volume_reg = 10;
		mixer &= ~0x04; /* enables C */
		break;
	default:
		Super(old_ssp);
		return;
	}

	/* setting fine tune of appropriate channel */
	*PSG_reg_select = fine_reg;
	*PSG_reg_write = note->fine;

	/* setting coarse tune of appropriate channel */
	*PSG_reg_select = coarse_reg;
	*PSG_reg_write = note->coarse;

	/* enabling appropriate channel on mixer */
	*PSG_reg_select = 7;
	*PSG_reg_write = mixer;

	/* setting volume of appropriate register */
	*PSG_reg_select = volume_reg; /* set channel A volume = 11 */
	*PSG_reg_write = VOL_ON;

	while (!Cconis()); /* tone now playing, await key */
		
	*PSG_reg_select = volume_reg; /* set channel A volume = 0 */
	*PSG_reg_write = 0;

	Cnecin();
	Super(old_ssp);
}
