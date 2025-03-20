#include "psg.h"
#include <osbind.h>

void write_psg(int reg, UINT8 val)
{
    volatile char *PSG_reg_select = PSG_REG_ADR;
    volatile char *PSG_reg_write = PSG_WRITE_ADR;
    long old_ssp = Super(0); /* enter privelaged mode */

    if (reg <= 15 && reg >= 0)
    {
        *PSG_reg_select = reg;
        *PSG_reg_write = val;
    }
    Super(old_ssp); /* exit privelaged mode */
};

UINT8 read_psg(int reg)
{
    volatile char *PSG_reg_select = PSG_REG_ADR;
    long old_ssp = Super(0); /* enter privelaged mode */
    UINT8 PSG_reg_val;

    if (reg <= 15 && reg >= 0){
        *PSG_reg_select = reg;
        PSG_reg_val = *PSG_reg_select;
    }
    Super(old_ssp); /* exit privelaged mode */
    return PSG_reg_val;
};

/*
void set_tone(int channel, Note *note);

void set_volume(int channel, int volume);

void enable_channel(int channel, bool tone_on, bool noise_on);

void stop_sound();
*/