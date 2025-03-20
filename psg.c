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


void set_tone(Channel channel, Note note){
    write_psg(channel.coarse_reg, note.coarse);
    write_psg(channel.fine_reg, note.fine);
};


void set_volume(Channel channel, int volume){
    if (volume >= 0 && volume <= 30){
        write_psg(channel.volume_reg, volume);
    }
};


void enable_channel(Channel channel, bool tone_on, bool noise_on){

    if ((tone_on == TRUE || tone_on == FALSE) && (noise_on == TRUE || noise_on == FALSE)){

    }
}

/*
void stop_sound();
*/