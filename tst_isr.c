
/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Mar.21, 2025

 FILE: tst_isr.c
 SUMMARY: Test program for VBL ISR
*******************************************************************************/
#include "base.h"
#include "screen.h"
#include "render.h"
#include "events.h"
#include "model.h"
#include "raster.h"
#include "input.h"
#include "bitmaps.h"
#include "clock.h"
#include "types.h"
#include "music.h"
#include "psg.h"
#include "vbl.h"
#include "isr.h"
#include <stdio.h>
#include <osbind.h>
#include <linea.h>

    UINT8 pre_buffer[32255]; /* 32255 = 320 * 200 + 15 */
    extern UINT8 IKBD_buffer[256];     
    extern void install_vectors();
    extern void remove_vectors();
    extern long kbd_read_char(bool update_head);
    extern bool kbd_is_waiting();
    extern void clear_kbd_buffer();
    int seconds = 0;
    int main ( ) {
        int prev = 0;
        Vector orig_vector = install_vector(VBL_ISR, vbl_isr);
    
        printf("%d seconds\r", seconds);
        fflush(stdout);
        while(seconds <= 10) {
            if (prev != seconds) {
                printf("%d seconds\r", seconds);
                fflush(stdout);
                prev = seconds;
            }
        }
        
        install_vector(VBL_ISR, orig_vector);
    
        return 0;
    }