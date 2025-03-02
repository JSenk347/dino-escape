#ifndef RASTER_H
#define RASTER_H

#define BYTES_PER_SCREEN 32000
#define HEIGHT_32 32
#define HEIGHT_16 16

typedef unsigned long UINT32;
typedef unsigned int UINT16;
void clear_rect(UINT16 *base, int x, int y, int width, int height);
void clear_square_32(UINT32 *base, int x, int y, int colour, int sqr_length);
void overwrite_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void plot_bitmap_16(UINT16 *base, int x, int y, 
        const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height, int mode);
void clear_screen(UINT16 *base, int pattern);
void plot_hline(unsigned short y, short mode);
void plot_vline(unsigned short x, short mode);
void plot_gline(unsigned short x1, unsigned short y1,
                unsigned short x2, unsigned short y2,
                short mode);
void plot_top_obs(UINT32 *base, int x, int gap_y);
void plot_bottom_obs(UINT32 *base, int x, int gap_y);
void plot_obstacles(UINT32 *base, int x, int gap_y);          
void plot_borders();
void plot_triangle_border(UINT32 *base, const UINT32 *bitmap_top,
                const UINT32 *bitmap_bottom);
void plot_top_start_button(UINT32 *base, const UINT32 *lt_top_start_bitmap,
	        const UINT32 *mid_lt_top_start_bitmap, const UINT32 *mid_rt_top_start_bitmap,
	        const UINT32 *rt_top_start_bitmap);
void plot_bottom_start_button(UINT32 *base, const UINT32 *lt_bottom_start_bitmap,
	        const UINT32 *mid_lt_bottom_start_bitmap, const UINT32 *mid_rt_bottom_start_bitmap,
	        const UINT32 *rt_bottom_start_bitmap);
void disable_cursor();
#endif