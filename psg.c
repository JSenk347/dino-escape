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

    if (reg <= 15 && reg >= 0)
    {
        *PSG_reg_select = reg;
        PSG_reg_val = *PSG_reg_select;
    }
    Super(old_ssp); /* exit privelaged mode */
    return PSG_reg_val;
}

void set_tone(Channel channel, Note note)
{
    if (channel <= CHANNEL_C && channel >= CHANNEL_A){
        switch (channel)
        {
        case CHANNEL_A:
            write_psg(A_COARSE_TONE_REG, note.coarse);
            write_psg(A_FINE_TONE_REG, note.fine);
            break;
        case CHANNEL_B:
            write_psg(B_COARSE_TONE_REG, note.coarse);
            write_psg(B_FINE_TONE_REG, note.fine);
            break;
        case CHANNEL_C:
            write_psg(C_COARSE_TONE_REG, note.coarse);
            write_psg(C_FINE_TONE_REG, note.fine);
            break;
        default:
            break;
        }
    }
    return;
}

/*
void set_volume(Channel channel, int volume){
    if (volume >= 0 && volume <= 30){
        write_psg(channel.volume_reg, volume);
    }
}
*/
void set_volume(Channel channel, int volume)
{
    if (volume <= MAX_VOLUME && volume >= MIN_VOLUME)
    {
        switch (channel)
        {
        case CHANNEL_A:
            write_psg(A_LEVEL_REG, volume);
            break;
        case CHANNEL_B:
            write_psg(B_LEVEL_REG, volume);
            break;
        case CHANNEL_C:
            write_psg(C_LEVEL_REG, volume);
            break;
        default:
            break;
        }
    }
}

/*
void enable_envelope(Channel channel, bool is_on){
    int vol = read_psg(channel.volume_reg);
    if (is_on){
        vol |= 0x11;
    } else {
        vol &= 0x01;
    }

    write_psg(channel.volume_reg, vol);
}
*/

void enable_envelope(Channel channel, bool is_on)
{
    if ((is_on || !is_on) && (channel <= CHANNEL_C && channel >= CHANNEL_A))
    {
        int vol;
        switch (channel)
        {
        case CHANNEL_A:
            vol = read_psg(A_LEVEL_REG);
            if (is_on){vol |= 0x11;}else{vol &= 0x01;}
            write_psg(A_LEVEL_REG, vol);
            break;
        case CHANNEL_B:
            vol = read_psg(B_LEVEL_REG);
            if (is_on){vol |= 0x11;}else{vol &= 0x01;}
            write_psg(B_LEVEL_REG, vol);
            break;
        case CHANNEL_C:
            vol = read_psg(C_LEVEL_REG);
            if (is_on){vol |= 0x11;}else{vol &= 0x01;}
            write_psg(C_LEVEL_REG, vol);
            break;
        default:
            break;
        }
    }
    return;
}

void enable_channel(Channel channel, bool tone_on, bool noise_on)
{
    /* 1 means OFF and 0 means ON in the mixer register*/
    UINT8 tone_bit, noise_bit, mixer_setting;

    if ((tone_on || !tone_on) && (noise_on || !noise_on) && (channel >= CHANNEL_A && channel <= CHANNEL_C))
    {
        tone_bit = 1 << channel;
        noise_bit = 1 << (channel + 3);

        mixer_setting = read_psg(MIXER_REG); /* reads current mixer setting */

        if (tone_on)
        {
            mixer_setting &= ~tone_bit;
        }
        else
        {
            mixer_setting |= tone_bit;
        }
        if (noise_on)
        {
            mixer_setting &= ~noise_bit;
        }
        else
        {
            mixer_setting |= noise_bit;
        }
        write_psg(MIXER_REG, mixer_setting);
    }
}

void set_noise(int tuning)
{
    if (tuning <= MAX_NOISE && tuning >= MIN_NOISE)
    {
        write_psg(NOISE_REG, tuning);
    }
    return;
}

void set_envelope(int shape, unsigned int sustain)
{
    if (shape <= MAX_ENVELOPE_SHAPE && shape >= MIN_ENVELOPE_SHAPE)
    {
        write_psg(11, (UINT8)sustain);        /* fine evelope reg */
        write_psg(12, (UINT8)(sustain >> 8)); /* coarse envelope reg */
        write_psg(13, (UINT8)shape);          /* envelope shape reg */
    }
}

void stop_sound()
{
    /* 0x3F = 0011 1111 is the mixer setting to disable all tone and noise on all channels */
    write_psg(MIXER_REG, 0x3F);
}

Scale init_scale()
{
    /*                g4        c5        e4        d4        D4        c4        C4         f4*/
    Scale scale = {{159, 0, 0}, {119, 0, 0}, {190, 0, 0}, {213, 0, 0}, {201, 0, 0}, {239, 0, 0}, {225, 0, 0}, {178, 0, 0}};
    return scale;
}


