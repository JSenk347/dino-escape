#include "raster.h"
//#include <osbind.h>



void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height){
	int i;
	int offset;

	offset = (x >> 5) + (y * 20);

	for (i = 0; i < height; i++){
		*(base + offset + (20 * i)) |= bitmap[i];
	}
	return;
}

void clear_screen(UINT16 *base, int pattern){
	register int i = 0;
	register UINT16 *loc = base;

		while (i++ < (BYTES_PER_SCREEN)/2){
			*(loc++) = pattern;
		}
}