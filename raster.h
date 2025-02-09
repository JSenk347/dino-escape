#ifndef RASTER_H
#define RASTER_H

#define BYTES_PER_SCREEN 32000
#define HEIGHT_32 32
#define HEIGHT_16 16

typedef unsigned long UINT32;
typedef unsigned int UINT16;

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void clear_screen(UINT16 *base, int pattern);
void plot_hline(unsigned short y, short mode);
void plot_vline(unsigned short x, short mode);
void plot_gline(unsigned short x1, unsigned short y1,
                unsigned short x2, unsigned short y2,
                short mode);
void plot_borders();
void disable_cursor();
#endif