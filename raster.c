#include "raster.h" 
#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#define XOR 2

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

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height){
	int i;
	int word_offset = (x >> 4) + (y * 40);
	int bit_shift = x & 15;

	for (i = 0; i < height; i++){
		UINT16 *pixel_addr = base + word_offset + (20 * i);

		if (bit_shift == 0){
			*pixel_addr |= bitmap[i];
		} else {
			pixel_addr[0] |= bitmap[i] >> bit_shift;
			pixel_addr[0] |= bitmap[i] << (32 - bit_shift);
		}
	}
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

	for (i = 390; i > 358; i--){
		plot_gline(311, i, 631, i, XOR);
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

