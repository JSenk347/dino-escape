/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.10, 2025
*******************************************************************************/
#include "raster.h" 
#include <stdio.h>
#include <linea.h>
#include <osbind.h>
#include "bitmaps.h"

#define XOR 2


/*******************************************************************************
	PURPOSE: To plot 32 bit bitmaps at specified x and y coordinates
	INPUT: 	- *base	pointer to the frame buffer
			- x	x coordinate you'd like to plot the bitmap at
			- y y coordinate you'd like to plot the bitmap at
			- *bitmap pointer to the bitmap you'd like to plot
			- height height of the bitmap you are plotting
	OUTPUT: N/A
*******************************************************************************/
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height)
{
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
	PURPOSE: To plot a horizontal line at a specified y coordinate
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
	X1 = (unsigned short) 0;
	Y1 = y;
	X2 = (unsigned short) 639;
	Y2 = y;
	LNMASK = 0xFFFF;/*Solid line style*/
	WMODE = mode; 	/*Writing mode*/
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
	Y2 = 399;
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
	PURPOSE: 	To plot the upper and lower borders of the game, exclusing the 
				ground and roof triangles (rocks)
	INPUT: 	N/A
	OUTPUT: N/A
*******************************************************************************/
void plot_borders()
{
	int i;

	/* plots the upper and lower border lines with plot_hline()*/
	for (i = 0; i < 50; i++){
		plot_hline(i, XOR);
		plot_hline(399 - i, XOR);
	}

	/*  plots lines to cancel out lines covering the score. will be implemented
		in scoring function later in development*/
	for (i = 390; i > 358; i--){
		plot_gline(311, i, 631, i, XOR);
	}
}

/*******************************************************************************
	PURPOSE: Plots an upper and lower 32x32 bitmap side by side across the
				screen to create the stalactite and stalagmite boarders on the
				top and bottom of the gameplay screen using plot_bitmap_32()
	INPUT: 	- *base	pointer to the frame buffer
			- *bitmap pointer to the uppper bitmap you'd like to plot
			- *bitmap pointer to the lower bitmap you'd like to plot
	OUTPUT:	N/A
*******************************************************************************/
void plot_triangle_border(UINT32 *base, const UINT32 *bitmap_top,
	const UINT32 *bitmap_bottom)
{
	int i;
	
	/* plots the upper border triangle line with plot_bitmap_32()*/
	for (i = 0; i < 640; i+=32){
		plot_bitmap_32((UINT32 *)base, i, 50, bitmap_top, HEIGHT_32);
	}

	/* plots the lower border triangle line with plot_bitmap_32()*/
	for (i = 0; i < 640; i+=32){
		plot_bitmap_32((UINT32 *)base, i, 314, bitmap_bottom, HEIGHT_32);
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
	PURPOSE: Plots the obstacles for the game using plot_bitmap_32() to create upper and lower 
	stalagtites and stalagmites for the bird to pass through or collide with.
	INPUT:	- *base	pointer to the frame buffer
			- x - x coordinate to plot the obstacle at
			- gap_y - y coordinate to plot the gap at
			- gap_height size of the gap between top and bottom obstacles
	OUTPUT:	N/A
*******************************************************************************/
void plot_obstacle(UINT32 *base, int x, int gap_y, int gap_height)
{
    
	plot_bitmap_32(base, x, gap_y + gap_height, obs_bitmap, 32);
	plot_bitmap_32(base, x, gap_y + gap_height + 32, obs_bitmap, 32);
	plot_bitmap_32(base, x, gap_y + gap_height + 64, obs_bitmap, 32);

	plot_bitmap_32(base, x, gap_y + gap_height - 172, obs_bitmap, 32);
    /* Plot the 32x32 bitmap on top of the bottom pipe */
    plot_bitmap_32(base, x, gap_y + gap_height - 32, obs_top_edge_bitmap, 32);

    /* Plot the 32x32 bitmap at the bottom of the top pipe */
    plot_bitmap_32(base, x, gap_y, obs_bottom_edge_bitmap, 32);
}
