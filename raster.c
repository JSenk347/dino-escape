#include "raster.h"
/*#include <stdio.h>*/
/*#include <osbind.h>*/ 
#include <linea.h>

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