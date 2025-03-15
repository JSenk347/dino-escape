/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Mar.2, 2025

 FILE: raster.c
 SUMMARY: Contains functions for all game raster graphics
*******************************************************************************/
#include "raster.h"
#include "bitmaps.h"
#include "model.h"
#include "events.h" 
#include <stdio.h>
#include <linea.h>
#include <osbind.h>

/*#define XOR 2
#define HALF_GAP 25*/


/*******************************************************************************
	PURPOSE: To plot 32 bit bitmaps at specified x and y coordinates (top left)
	INPUT: 	- *base	pointer to the frame buffer
			- x	x coordinate you'd like to plot the bitmap at
			- y y coordinate you'd like to plot the bitmap at
			- *bitmap pointer to the bitmap you'd like to plot
			- height height of the bitmap you are plotting
			- mode .... not done?
	OUTPUT: N/A
*******************************************************************************/

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height) {
    int i;
    int word_offset = (x >> 5) + (y * 20); /* Word-aligned base offset */
    int bit_shift = x & 31; /* Offset within the 32-bit word */

    for (i = 0; i < height; i++) {
        UINT32 *pixel_addr = base + word_offset + (20 * i);

        if (bit_shift == 0) {
            /* Perfectly aligned on a 32-bit boundary */
            *pixel_addr |= bitmap[i];
        } else {
            /* Bitmap is split across two 32-bit words */
            pixel_addr[0] |= bitmap[i] >> bit_shift; /* First part in current word */
            pixel_addr[1] |= bitmap[i] << (32 - bit_shift); /* Remaining part in next word */
        }
    }
}

/******************************************************************************
	PURPOSE: Clears the 32x32 block given by the x,y cordinates by calling
				plot_bitmap_32 to overwrite the block with either all white or
				all black
	INPUT: 	- *base	pointer to the frame buffer
			- x	x coordinate you'd like to plot the bitmap at
			- y y coordinate you'd like to plot the bitmap at
			- colour either 1 (black) or 0 (white)
			- sqr_length integer of the height/width of the square to clear
	OUTPUT: N/A
******************************************************************************/
void clear_square_32(UINT32 *base, int x, int y, int colour, int sqr_length) {
    int row, col;
    int screen_longs_per_row = 640 / 32;
	int word_offset = x >> 5; /* Calculate the initial word offset */
    int bit_shift = x & 31;   /* Calculate the bit shift within the first word */

    for (row = y; row < y + sqr_length; row++) {
        UINT32 *pixel_addr = base + (row * screen_longs_per_row) + word_offset;
        
        for (col = 0; col < ((sqr_length + bit_shift + 31) >> 5); col++) { 
			/* First partial word (if any) */
			if (col == 0 && bit_shift != 0) {
                UINT32 mask = ~((1 << bit_shift) - 1); 
                pixel_addr[col] = (pixel_addr[col] & mask) | (colour & ~mask);
            }
			/* Second partial word (if any) */
			else if (col == ((sqr_length + bit_shift + 31) >> 5) - 1 && (sqr_length + bit_shift) % 32 != 0) {
				UINT32 mask = (1 << (32 - (sqr_length + bit_shift) % 32)) - 1;
                pixel_addr[col] = (pixel_addr[col] & ~mask) | (colour & mask);
			}
			/* Full words */
			else {
				pixel_addr[col] = colour;
			}
        }
    }
}

/*******************************************************************************
	PURPOSE: 
	INPUT: 	- *base	pointer to the frame buffer
			- x	x coordinate you'd like to 
			- y y coordinate you'd like to 
			- 
	OUTPUT: N/A
*******************************************************************************/
void clear_region(UINT32 *base, int x, int y, unsigned int pattern) {
    int i;
    int word_offset = (x >> 5) + (y * 20); /* Word-aligned base offset */
    int bit_shift = x & 31; /* Offset within the 32-bit word */

    for (i = 0; i < 32; i++) {
        UINT32 *pixel_addr = base + word_offset + (20 * i);

        if (bit_shift == 0) {
            /* Perfectly aligned on a 32-bit boundary */
            *pixel_addr = pattern;  /*Overwrite with the pattern*/ 
        } else {
            /* The region spans two words */
            pixel_addr[0] = (pixel_addr[0] & ~(0xFFFFFFFF >> bit_shift)) | (pattern >> bit_shift);
            pixel_addr[1] = (pixel_addr[1] & ~(0xFFFFFFFF << (32 - bit_shift))) | (pattern << (32 - bit_shift));
        }
    }
}

/*******************************************************************************
	PURPOSE: To clear everything that is between the upper and lower cave borders
	INPUT: 	- *base	pointer to the frame buffer
	OUTPUT: N/A
*******************************************************************************/
void clear_cave_region(UINT32 *base) {
	int i;
	int k;
	int word_offset = (34) * 20; /* don't ask my why its 34. i don't know */
	base += word_offset;

	for (i = (T_BORDER_Y + 1); i < (B_BORDER_Y - 2); i++){ /* also don't ask why it's -2. don't know also */
		for (k = 0; k < 20; k++){
			base[k] = 0x00000000;
		}
		base += 20;
	}
}

/*******************************************************************************
	PURPOSE: To plot 16 bit bitmaps at specified x and y coordinates
	INPUT: 	- *base	pointer to the frame buffer
			- x	x coordinate you'd like to plot the bitmap at
			- y y coordinate you'd like to plot the bitmap at
			- *bitmap pointer to the bitmap you'd like to plot
			- height height of the bitmap you are plotting
	OUTPUT: N/A
*******************************************************************************/
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height)
{
	int i;
	int word_offset = (x >> 4) + (y * 40); /* Word-aligned base offset*/
	int bit_shift = x & 15; /* Offset within the 32-bit words */

	for (i = 0; i < height; i++){
		UINT16 *pixel_addr = base + word_offset + (20 * i);

		if (bit_shift == 0){
			/* the bitmap is aligned with the frame buffer words*/
			*pixel_addr |= bitmap[i];
		} else {
			/* bitmap is split across two 32 bit words */
			pixel_addr[0] |= bitmap[i] >> bit_shift; /* first part is in the current word*/
			pixel_addr[0] |= bitmap[i] << (32 - bit_shift); /* second part is in the next word*/
		}
	}
};

/******************************************************************************
	PURPOSE: To clear the screen and display all white
	INPUT: 	- *base pointer to the frame buffer
			- pattern the pixel state to fill the screen with (0/1)
	OUTPUT: N/A
******************************************************************************/
void clear_screen(UINT16 *base, int pattern)
{
	register int i = 0;
	register UINT16 *loc = base;

		while (i++ < (BYTES_PER_SCREEN)/2){
			*(loc++) = pattern;
		}
}

/******************************************************************************
	PURPOSE: Plots a horizontal line at the given y coordinate
	INPUT: 	- y the y coordinate to plot the line at
			- mode the behaviour of the line:
				- 0: replace
				- 1: or
				- 2: xor
				- 3: and
	OUTPUT: N/A
******************************************************************************/
void plot_hline(unsigned short y, short mode)
{
	X1 = (unsigned short) L_BORDER_X;
	Y1 = y;
	X2 = (unsigned short) R_BORDER_X;
	Y2 = y;
	LNMASK = 0xFFFF;	/* Solid line style */
	WMODE = mode; 		/* Writing mode */
	LSTLIN = 0;
	linea3();
}

/******************************************************************************
	PURPOSE: To plot a vertical line at a specified x coordinate
	INPUT: 	- x the x coordinate to plot the line at
			- mode the behaviour of the line:
				- 0: replace
				- 1: or
				- 2: xor
				- 3: and				
	OUTPUT: N/A
******************************************************************************/
void plot_vline(unsigned short x, short mode)
{
	X1 = x;
	Y1 = 0;
	X2 = x;
	Y2 = 400;
	LNMASK = 0xFFFF;
	WMODE = mode;
	LSTLIN = 0;
	linea3();
}

/*****************************************************************************
	PURPOSE: To plot a general line at specified x1, y1, x2, and y2 coordinates
	INPUT:	- x1 the x coordinate of the start of the line
			- y1 the y coordinate of the start of the line
			- x2 the x coordinate of the end of the line
			- y2 the y coordinate of the end of the line
	OUTPUT: N/A
*****************************************************************************/
void plot_gline(unsigned short x1, unsigned short y1,
				unsigned short x2, unsigned short y2,
				short mode)
{
	/* updating the line-a library variables*/
	X1 = x1; 
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	LNMASK = 0xFFFF;
	WMODE = mode;
	LSTLIN = 0;

	/* plotting the line */
	linea3();
}

/*******************************************************************************
	PURPOSE: Plots the upper and lower borders of the game
	INPUT: 	N/A
	OUTPUT: N/A
*******************************************************************************/
void plot_borders()
{
	int i;

	/* plots the upper and lower border lines with plot_hline() */
	for (i = 0; i < 50; i++) {
		plot_hline(i, XOR);
		plot_hline(399 - i, XOR);
	}

	/*  plots lines to cancel out lines covering the score */
	for (i = 390; i > 358; i--) {
		plot_gline(505, i, 631, i, XOR);
	}
}

/*******************************************************************************
	PURPOSE: Plots the upper and lower borders of the game, excluding the 
				ground and roof triangles (rocks). FOR PHASE 2 ONLY.
	INPUT: 	N/A
	OUTPUT: N/A
*******************************************************************************/
void plot_borders_raster()
{
	int i;

	/* plots the upper and lower border lines with plot_hline() */
	for (i = 0; i < 50; i++) {
		plot_hline(i, XOR);
		plot_hline(399 - i, XOR);
	}

	/*  plots lines to cancel out lines covering the score */
	for (i = 390; i > 358; i--) {
		plot_gline(312, i, 631, i, XOR);
	}
}

/*******************************************************************************
	PURPOSE: Plots the top three 32x32 bitmaps to create the top half of the 
				start button
	INPUT:	- *base	pointer to the frame buffer
			- *bitmap pointer to the top left corner bitmap you'd like to plot
			- *bitmap pointer to the top middle-left corner bitmap you'd like to plot
			- *bitmap pointer to the top middle-right corner bitmap you'd like to plot
			- *bitmap pointer to the top right corner bitmap you'd like to plot
	OUTPUT:	N/A
*******************************************************************************/
void plot_top_start_button(UINT32 *base, const UINT32 *lt_top_start_bitmap,
	const UINT32 *mid_lt_top_start_bitmap, const UINT32 *mid_rt_top_start_bitmap,
	const UINT32 *rt_top_start_bitmap)
{
	plot_bitmap_32((UINT32 *)base, 256, 168, lt_top_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 288, 168, mid_lt_top_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 320, 168, mid_rt_top_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 352, 168, rt_top_start_bitmap, HEIGHT_32);
}

/*******************************************************************************
	PURPOSE: Plots the bottom three 32x32 bitmaps to create the bottom half of
				the start button using plot_bitmap_32()
	INPUT:	- *base	pointer to the frame buffer
			- *bitmap pointer to the bottom left corner bitmap you'd like to plot
			- *bitmap pointer to the bottom middle-left corner bitmap you'd like to plot
			- *bitmap pointer to the bottom middle-right corner bitmap you'd like to plot
			- *bitmap pointer to the bottom right corner bitmap you'd like to plot
	OUTPUT: N/A
*******************************************************************************/
void plot_bottom_start_button(UINT32 *base, const UINT32 *lt_bottom_start_bitmap,
	const UINT32 *mid_lt_bottom_start_bitmap, const UINT32 *mid_rt_bottom_start_bitmap,
	const UINT32 *rt_bottom_start_bitmap)
{
	plot_bitmap_32((UINT32 *)base, 256, 200, lt_bottom_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 288, 200, mid_lt_bottom_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 320, 200, mid_rt_bottom_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 352, 200, rt_bottom_start_bitmap, HEIGHT_32);
}

/*******************************************************************************
	PURPOSE: To disable the cursor and remove it from the screen
	INPUT: 	N/A
	OUTPUT: N/A
*******************************************************************************/
void disable_cursor()
{
	printf("\033f"); /* excutes "ESC + F" which disables the cursor*/
	fflush(stdout); /* ensures above line is output immediatley*/
}

/*******************************************************************************
	PURPOSE: To plot the top obstacle of the wall object
	INPUT: - base: pointer to the first longword address of the frame buffer
		   - x: the top left x of the obstacle
		   - y: the top left y of the obstacle
		   - gap_y: the gap associated to the wall
		   - mode: the write/delete mode for plot_bitmap_32()
	OUTPUT: N/A
*******************************************************************************/
void plot_top_obs(UINT32 *base, int x, int gap_y, int mode)
{
	int edge_y = gap_y - HALF_GAP; 
    plot_bitmap_32(base, x, edge_y - HEIGHT_32, obs_bottom_edge_bitmap, HEIGHT_32);

}

/*******************************************************************************
	PURPOSE: To plot the bottom obstacle of the wall object
	INPUT: - base: pointer to the first longword address of the frame buffer
		   - x: the top left x of the obstacle
		   - y: the top left y of the obstacle
		   - gap_y: the gap associated to the wall
		   - mode: the write/delete mode for plot_bitmap_32()
	OUTPUT: N/A
*******************************************************************************/
void plot_bottom_obs(UINT32 *base, int x, int gap_y, int mode)
{
	int edge_y = gap_y + HALF_GAP; 
    plot_bitmap_32(base, x, edge_y, obs_top_edge_bitmap, HEIGHT_32);
}

/*******************************************************************************
    PURPOSE: Plots the top and bottom obstacle edge bitmaps to the screen.
    INPUT:  - base: 32 bit base address of the screen
			- x: x coordinate to plot horizontal position of each obstacle
				bitmap
			- gap_y: the gap associated to the wall
		   - mode: the write/delete mode for plot_bitmap_32()
    OUTPUT: - N/A
*******************************************************************************/
void plot_obstacles(UINT32 *base, int x, int gap_y, int mode){
	plot_top_obs(base, x, gap_y, mode);
	plot_bottom_obs(base, x, gap_y, mode);
}