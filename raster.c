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
#include "types.h"
/*#define XOR 2
#define HALF_GAP 25*/

/*******************************************************************************
	PURPOSE: To plot 32 bit bitmaps at specified x and y coordinates (top left)
	INPUT: 	- *base	pointer to the frame buffer
			- x	x coordinate you'd like to plot the bitmap at
			- y y coordinate you'd like to plot the bitmap at
			- *bitmap pointer to the bitmap you'd like to plot
			- height height of the bitmap you are plotting
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

/*******************************************************************************
	PURPOSE: Clears a 32x32 block in the given frame buffer in the spot of the 
				given x,y cordinates (top left)
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
	int word_offset = (50) * 20; /* don't ask my why its 34. i don't know */
	base += word_offset;

	for (i = (T_BORDER_Y + 1); i < (B_BORDER_Y); i++){ /* also don't ask why it's -2. don't know also */
		for (k = 0; k < 2; k++){
			base[k] = 0x00000000;
		}
		base += 20;
	}
}



/*******************************************************************************
	PURPOSE: Clears a specific rectangular region on the far left side of the
				screen
	INPUT: 	- *base	pointer to the frame buffer
	OUTPUT: N/A
*******************************************************************************/
void clear_far_left(UINT32 *base){
	int y;
	int x = L_BORDER_X;
	for (y = T_BORDER_Y + 1; y < B_BORDER_Y - 32; y += 32){
		clear_region(base, x, y, 0x00000000);
		clear_region(base, x + 2, y, 0x00000000);
	}
	clear_region(base, x, B_BORDER_Y - 32, 0x00000000);
	clear_region(base, x + 2, B_BORDER_Y - 32, 0x00000000);
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
	PURPOSE: Plots a horizontal line with the given x1, x2, and y coordinates
				where the line starts at (x1,y) and ends at (x2,y)
	INPUT: 	- *base	pointer to the frame buffer
			- y the y coordinate to plot the line at
			- x1 the x coordinate where the line begins
			- x2 the x coordinate where the line ends
	OUTPUT: N/A
******************************************************************************/
void plot_bline(UINT32 *base, int y, int x1, int x2) {
    UINT32 p1, p2;
    int row1, row2, i;
    int shift_F, shift_B;
    UINT32 *place = base + y * (80 / 4); /* 80 bytes / 4 bytes per longword */

    row1 = x1 >> 5; /* Equivalent to x1 / 32 */
    row2 = x2 >> 5; /* Equivalent to x2 / 32 */
    shift_F = x1 & 31; /* Equivalent to x1 % 32 */
    shift_B = 31 - (x2 & 31); /* Equivalent to 31 - (x2 % 32) */

    if (row1 == row2) {
        p1 = SOLID_32 >> shift_F;
        p2 = SOLID_32 << shift_B;
        *(place + row1) = p1 & p2;
    } else {
        p1 = SOLID_32 >> shift_F;
        p2 = SOLID_32 << shift_B;
        *(place + row1) = p1;
        for (i = row1 + 1; i < row2; i++) {
            *(place + i) = SOLID_32;
        }
        *(place + row2) = p2;
    }
}

/******************************************************************************
	PURPOSE: Plots a horizontal line across the full game screen at the given 
				y coordinate
	INPUT: 	- y the y coordinate to plot the line at
			- mode the behaviour of the line:
				- 0: replace
				- 1: or		(will plot a black line over all previous bits)
				- 2: xor	
				- 3: and
	OUTPUT: N/A
******************************************************************************/
/*void plot_hline(unsigned short y, short mode)
{
	/* Sets line start point coordinates 
	X1 = (unsigned short) L_BORDER_X;
	Y1 = y;
	
	/* Sets line end point coordinates 
	X2 = (unsigned short) R_BORDER_X;
	Y2 = y;

	/* Sets colour to black (linea document) 
	COLBIT0 = 1;
    COLBIT1 = 1;
    COLBIT2 = 1;
    COLBIT3 = 1;
	
	LNMASK = 0xFFFF;	/* Solid line style (pattern) 
	WMODE = mode; 		/* Writing mode 
	LSTLIN = -1; 		/* changed from 0 to -1 as per linea document
	linea3();
}*/

/******************************************************************************
	PURPOSE: To plot a 2 pixel thick vertical line with the given x, y1, and y2
				coordinates where the line starts at (x,y1) and ends at (x,y2)
	INPUT: 	- *base	pointer to the frame buffer
			- x the x coordinate to plot the line at
			- y1 the y coordinate where the line begins
			- y2 the y coordinate where the line end
			- mode the behaviour of the line:
				- 0: CLEAR
				- 1: SET			
	OUTPUT: N/A
******************************************************************************/
void plot_vline(UINT8 *base, int x, int y1, int y2, int mode) {	
	UINT8 set_pattern, clear_pattern; 
	UINT8 *pixel_addr; 
	
	set_pattern = 1 << (7 - (x & 7));
	clear_pattern = ~(1 << (7 - (x & 7))); 
	
	pixel_addr = base + y1 * 80 + (x >> 3); 
	for ( ; y1 <= y2; y1++) { 
		if (mode == 1) {
			*pixel_addr |= (set_pattern);
		} else {
			*pixel_addr &= (clear_pattern);
		}
		pixel_addr = pixel_addr + 80;
	}
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
/*void plot_vline(unsigned short x, short mode)
{
	X1 = x;
	Y1 = 0;
	X2 = x;
	Y2 = 400;
	LNMASK = 0xFFFF;
	WMODE = mode;
	LSTLIN = 0;
	linea3();
}*/

/*****************************************************************************
	PURPOSE: To plot a general line at specified x1, y1, x2, and y2 coordinates
	INPUT:	- x1 the x coordinate of the start of the line
			- y1 the y coordinate of the start of the line
			- x2 the x coordinate of the end of the line
			- y2 the y coordinate of the end of the line
			- mode the behaviour of the line:
				- 0: replace
				- 1: or
				- 2: xor	
				- 3: and
			- set_bit determines the color of the line (1: black 0: white)
	OUTPUT: N/A
*****************************************************************************/
/*void plot_gline(unsigned short x1, unsigned short y1,
				unsigned short x2, unsigned short y2,
				short mode, int set_bit)
{
	/* Sets line start point coordinates 
	X1 = x1; 
	Y1 = y1;

	/* Sets line end point coordinates 
	X2 = x2;
	Y2 = y2;

	/* Sets colour to 0 (white) or 1 (black) (linea document) 
	COLBIT0 = set_bit;
    COLBIT1 = set_bit;
    COLBIT2 = set_bit;
    COLBIT3 = set_bit;
	

	if (set_bit == 0) {
		LNMASK = 0x0000;
	}
	else {
		LNMASK = 0xFFFF;
	}
	WMODE = mode; 		/* Writing mode 
	LSTLIN = -1; 		/* changed from 0 to -1 as per linea document

	/*LNMASK = 0xFFFF;
	WMODE = mode;
	LSTLIN = 0;

	/* plotting the line 
	linea3();
} */

/*******************************************************************************
	PURPOSE: Plots the upper and lower borders of the game
	INPUT: 	N/A
	OUTPUT: N/A
*******************************************************************************/
void plot_borders(UINT32 *base) {
	int i;

	/* plots the upper and lower border lines with plot_hline() */
	for (i = 0; i < 50; i++) {
		plot_bline(base, i, L_BORDER_X, R_BORDER_X);		/* upper border */
		plot_bline(base, 399 - i, L_BORDER_X, R_BORDER_X);	/* lower border*/
		
		/*plot_hline(i, OR);			/* upper border */
		/*plot_hline(399 - i, OR);	/* lower border*/
	}

	/* NO LONGER NEEDED plots lines to cancel out lines covering the score */
	/*for (i = 390; i > 358; i--) {
		plot_gline(505, i, 631, i, XOR);
	}*/
}

/*******************************************************************************
	PURPOSE: Plots the upper and lower borders of the game, excluding the 
				ground and roof triangles (rocks). FOR PHASE 2 ONLY.
	INPUT: 	N/A
	OUTPUT: N/A
*******************************************************************************/
/*void plot_borders_raster()
{
	int i;

	/* plots the upper and lower border lines with plot_hline() 
	for (i = 0; i < 50; i++) {
		plot_hline(i, XOR);
		plot_hline(399 - i, XOR);
	}

	/*  plots lines to cancel out lines covering the score
	for (i = 390; i > 358; i--) {
		plot_gline(312, i, 631, i, XOR, 1);
	}
}*/

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
	plot_bitmap_32((UINT32 *)base, 255, 167, lt_top_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 287, 167, mid_lt_top_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 319, 167, mid_rt_top_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 351, 167, rt_top_start_bitmap, HEIGHT_32);
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
	plot_bitmap_32((UINT32 *)base, 255, 199, lt_bottom_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 287, 199, mid_lt_bottom_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 319, 199, mid_rt_bottom_start_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 351, 199, rt_bottom_start_bitmap, HEIGHT_32);
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
/*******************************************************************************
    PURPOSE: Saves the mouse background to the mouse_bkgd array at the given x and y
				coordinates. The mouse background is 16x16 pixels in size.
    INPUT:  - base: 32 bit base address of the screen
			- x: x coordinate to plot horizontal position of each obstacle
			- y: y coordinate to plot vertical position of each obstacle
    OUTPUT: N/A
*******************************************************************************/
void save_mouse_bkgd(UINT32 *base, int x, int y) {
	int i, j;
	
	for(i = 0, j = 0; i < MOUSE_HEIGHT; i++) {
		mouse_bkgd[j++] = *(base + (y + i) * 20 + (x >> 5));
		mouse_bkgd[j++] = *(base + (y + i) * 20 + ((x >> 5) + 1));
	}
}

/*******************************************************************************
    PURPOSE: Restores the mouse background to the screen at the given x and y
				coordinates
    INPUT:  - base: 32 bit base address of the screen
			- x: x coordinate to plot horizontal position of each obstacle		
			-y: y coordinate to plot vertical position of each obstacle
    OUTPUT: N/A
*******************************************************************************/
void restore_mouse_bkgd(UINT32 *base, int x, int y) {
	int i, j;
	
	for(i = 0, j = 0; i < MOUSE_HEIGHT; i++) {
		*(base + (y + i) * 20 + (x >> 5)) = mouse_bkgd[j++];
		*(base + (y + i) * 20 + ((x >> 5) + 1)) = mouse_bkgd[j++];
	}
}

/*******************************************************************************
    PURPOSE: Plots the mouse bitmap at the given x and y coordinates. The mouse
				bitmap is 16x16 pixels in size. The mouse bitmap is XORed with the
    INPUT:  - base: 16 bit base address of the screen
			- x: x coordinate to plot horizontal position of each obstacle
			- y: y coordinate to plot vertical position of each obstacle
    OUTPUT: N/A
*******************************************************************************/
void plot_mouse(UINT16 *base, int x, int y, UINT16 *bitmap) {
	int i, j;
	
	for(i = 0, j = 0; i < MOUSE_HEIGHT; i++) {
		*(base + (y + i) * 40 + (x >> 4)) ^= *(bitmap + j) >> (x & 15);
		*(base + (y + i) * 40 + ((x >> 4) + 1)) ^= *(bitmap + j++) << (16 - (x & 15));
	}
}
