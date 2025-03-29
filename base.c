/*******************************************************************************
 AUTHORS:      Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE:       COMP2659-001
 INSTRUCTOR:   Tim Reimer
 DATE:         Mar.23, 2025

 FILE:         base.c
 PURPOSE:      Physbase replicator for the Atari ST
*******************************************************************************/
#include "screen.h" 

/*******************************************************************************
    PURPOSE: Get the base address of the screen 
    INPUT:  N/A
    OUTPUT: UINT8 *base - base address of the screen
*******************************************************************************/
UINT8 *get_video_base() {
    long base; /* base pointer */
	long ogSSP = Super(0); /* Save stack pointer and enter super mode */

    base = ((long)(*(volatile UINT8 *)0xFFFF8201) << 16) | /*High byte shifted to bits 23–16 */
               ((long)(*(volatile UINT8 *)0xFFFF8203) << 8); /* Mid byte shifted to bits 15–8 */

    Super(ogSSP);
    return (UINT8*)(base);
}


