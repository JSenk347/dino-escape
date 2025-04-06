#ifndef RASTER_H
#define RASTER_H
#include "types.h"
#include "vbl.h"
#include "ISR.H"
#define BYTES_PER_SCREEN 32000
#define SOLID_32    		0xFFFFFFFF
#define CLEAR_32			0x00000000
#define BITS_IN_LONGWORD 	32
#define HEIGHT_32 32
#define HEIGHT_16 16
#define OR 1
#define XOR 2
#define AND 3
#define HALF_GAP 25
#define MOUSE_WIDTH 16
#define MOUSE_HEIGHT 19


void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void clear_rect(UINT16 *base, int x, int y, int width, int height);
void overwrite_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void plot_bitmap_16(UINT16 *base, int x, int y, 
        const UINT16 *bitmap, unsigned int height);
void clear_screen(UINT16 *base, int pattern);
void plot_bline(UINT32 *base, int y, int x1, int x2);
void plot_vline(UINT8 *base, int x, int y1, int y2, int mode);
/*void plot_hline(unsigned short y, short mode);*/
/*void plot_vline(unsigned short x, short mode); */
/*void plot_gline(unsigned short x1, unsigned short y1,
                unsigned short x2, unsigned short y2,
                short mode, int set_bit);*/
void plot_top_obs(UINT32 *base, int x, int gap_y, int mode);
void plot_bottom_obs(UINT32 *base, int x, int gap_y, int mode);
void plot_obstacles(UINT32 *base, int x, int gap_y, int mode);          
void plot_borders(UINT32 *base);
/*void plot_borders_raster(); /* only used for stage 2 */
void plot_top_start_button(UINT32 *base, const UINT32 *lt_top_start_bitmap,
	        const UINT32 *mid_lt_top_start_bitmap, const UINT32 *mid_rt_top_start_bitmap,
	        const UINT32 *rt_top_start_bitmap);
void plot_bottom_start_button(UINT32 *base, const UINT32 *lt_bottom_start_bitmap,
	        const UINT32 *mid_lt_bottom_start_bitmap, const UINT32 *mid_rt_bottom_start_bitmap,
	        const UINT32 *rt_bottom_start_bitmap);
void disable_cursor();
void clear_far_left(UINT32 *base);
void clear_region(UINT32 *base, int x, int y, unsigned int pattern);
void clear_cave_region(UINT32 *base);
/* Saves mouse background, as a long, to an array in bitmaps file */
void save_mouse_bkgd(UINT32 *base, int x, int y);
/* restores mouse background, as a long, from an array in bitmaps file */
void restore_mouse_bkgd(UINT32 *base, int x, int y);

/* Prints a mouse to the screen  (i.e a print bitmap)*/
void plot_mouse(UINT16 *base, int x, int y, UINT16 *bitmap);

#endif