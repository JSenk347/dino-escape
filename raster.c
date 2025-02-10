#include "raster.h" 
#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#define XOR 2

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height){
	int i;
	int offset;

	offset = (x >> 5) + (y * 20);

	for (i = 0; i < height; i++){
		*(base + offset + (20 * i)) |= bitmap[i];
	}
	return;
}

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height){
	int i;
	int offset;

	offset = (x >> 4) + (y * 40);

	for (i = 0; i < height; i++){
		*(base + offset + (40 * i)) |= bitmap[i];
	}
	return;
};

void clear_screen(UINT16 *base, int pattern){
	register int i = 0;
	register UINT16 *loc = base;

		while (i++ < (BYTES_PER_SCREEN)/2){
			*(loc++) = pattern;
		}
}

/*
	MODES:
		- 0: replace
		- 1: or
		- 2: xor
		- 3: and
	SUMMARY:
		Plots a horizontal line at a specified y coordinate. 
		linea0() must be called before this function.
*/
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

void plot_gline(unsigned short x1, unsigned short y1,
				unsigned short x2, unsigned short y2,
				short mode)
{
	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	LNMASK = 0xFFFF;
	WMODE = mode;
	LSTLIN = 0;
	linea3();
}

void plot_borders()
{
	int i;

	for (i = 0; i < 50; i++){
		plot_hline(i, XOR);
		plot_hline(399 - i, XOR);
	}
}

/*
	Hides the cursor
*/
void disable_cursor()
{
	printf("\033f");
	fflush(stdout);
}

void plot_obstacle_32(UINT32 *base, int x, int gap_y, int gap_height, int pipe_width, int screen_height, int thickness) 
{
    int i;

    /* Draw top pipe outline */
    for (i = 0; i < thickness; i++) {
        plot_gline(x + i, 0, x + i, gap_y, XOR);
        plot_gline(x + pipe_width - i - 1, 0, x + pipe_width - i - 1, gap_y, XOR);
    }
    plot_gline(x, 0, x + pipe_width - 1, 0, XOR);
    plot_gline(x, gap_y, x + pipe_width - 1, gap_y, XOR);

    /* Draw bottom pipe outline */
    for (i = 0; i < thickness; i++) {
        plot_gline(x + i, gap_y + gap_height, x + i, screen_height - 1, XOR);
        plot_gline(x + pipe_width - i - 1, gap_y + gap_height, x + pipe_width - i - 1, screen_height - 1, XOR);
    }
    plot_gline(x, gap_y + gap_height, x + pipe_width - 1, gap_y + gap_height, XOR);
    plot_gline(x, screen_height - 1, x + pipe_width - 1, screen_height - 1, XOR);
}

