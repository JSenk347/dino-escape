#ifndef RASTER_H
#define RASTER_H


typedef unsigned long UINT32
typedef unsigned int UINT16

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void clear_screen(UINT16 *base, int pattern);

#endif
