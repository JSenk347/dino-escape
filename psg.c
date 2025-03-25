#include "psg.h"
#include <osbind.h>
#include <stdio.h>

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
}

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
}


void set_tone(Channel channel, Note note){
    write_psg(channel.coarse_reg, note.coarse);
    write_psg(channel.fine_reg, note.fine);
}


void set_volume(Channel channel, int volume){
    if (volume >= 0 && volume <= 30){
        write_psg(channel.volume_reg, volume);
    }
}

void enable_envelope(Channel channel, bool is_on){
    int vol = read_psg(channel.volume_reg);
    if (is_on){
        vol |= 0x11;
    } else {
        vol &= 0x01;
    }
    
    write_psg(channel.volume_reg, vol);
}


void enable_channel(UINT8 channel, bool tone_on, bool noise_on){
    /* 1 means OFF and 0 means ON in the mixer register*/
    UINT8 tone_bit, noise_bit, mixer_setting;

    if ((tone_on || !tone_on) && (noise_on || !noise_on)
        && (channel >= CHANNEL_A && channel <= CHANNEL_C))
    {
        tone_bit = 1 << channel;
        noise_bit = 1 << (channel + 3);

        mixer_setting = read_psg(MIXER_REG); /* reads current mixer setting */

        if (tone_on){
            mixer_setting &= ~tone_bit;
        } else {
            mixer_setting |= tone_bit;
        }
        if (noise_on){
            mixer_setting &= ~noise_bit;
        } else {
            mixer_setting |= noise_bit;
        }
        write_psg(MIXER_REG, mixer_setting);
    }
}

void set_noise(int tuning){
    if (tuning <= MAX_NOISE && tuning >= MIN_NOISE){
        write_psg(NOISE_REG, tuning);
    }
    return;
}

void set_envelope(int shape, unsigned int sustain){
    if (shape <= MAX_ENVELOPE_SHAPE && shape >= MIN_ENVELOPE_SHAPE){
        write_psg(11, (UINT8)sustain); /* fine evelope reg */
        write_psg(12, (UINT8)(sustain >> 8)); /* coarse envelope reg */
        write_psg(13, (UINT8)shape); /* envelope shape reg */
    }
}

void stop_sound(){
    /* 0x3F = 0011 1111 is the mixer setting to disable all tone and noise on all channels */
    write_psg(MIXER_REG, 0x3F);
}

Scale init_scale()
{
    /*                g4        c5        e4        d4        D4        c4        C4         f4*/
    Scale scale = {{159, 0}, {119, 0}, {190, 0}, {213, 0}, {201, 0}, {239, 0}, {225, 0}, {178, 0}};
    return scale;
}

void init_channels(Channel channels[NUM_CHANNELS])
{
    channels[CHANNEL_A].fine_reg = 0;
    channels[CHANNEL_A].coarse_reg = 1;
    channels[CHANNEL_A].volume_reg = 8;
    channels[CHANNEL_B].fine_reg = 2;
    channels[CHANNEL_B].coarse_reg = 3;
    channels[CHANNEL_B].volume_reg = 9;
    channels[CHANNEL_C].fine_reg = 4;
    channels[CHANNEL_C].coarse_reg = 5;
    channels[CHANNEL_C].volume_reg = 10;
}
