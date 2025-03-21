#include "game_snd.h"
#include <osbind.h>

void play_note(Note *note) {
	volatile char *PSG_reg_select = 0xFF8800;
	volatile char *PSG_reg_write  = 0xFF8802;
	long old_ssp = Super(0);
	
	
	*PSG_reg_select = 0;		/* set channel A fine tune = 248 */
	/**PSG_reg_write  = 248;       Higher pitch: decrease value */
	*PSG_reg_write = note -> fine;

	*PSG_reg_select = 1;		/* set channel A coarse tune = 0 
	*PSG_reg_write  = 0; */
	*PSG_reg_write = note -> coarse;

	*PSG_reg_select = 7;		/* enable channel A on mixer */
	*PSG_reg_write  = 0x3E;

	*PSG_reg_select = 8;		/* set channel A volume = 11 */
	*PSG_reg_write  = VOL_ON;

	while (!Cconis())		/* tone now playing, await key */
		;

	*PSG_reg_select = 8;		/* set channel A volume = 0 */
	*PSG_reg_write  = 0;

	Cnecin();
	Super(old_ssp);
}
