#include "raster.h"
#include "bitmaps.h"

#include <stdio.h>
#include <osbind.h>
#include <linea.h>

#define REPLACE 0
#define OR 1
#define XOR 2
#define AND 3


int main()
{
	void *base = Physbase();
	linea0(); /*needed to call any plot line functions*/

	disable_cursor();
	clear_screen((UINT16 *)base, 0);

	/* LINE PLOTTING */
  
	plot_borders();
  /* Obstacle Plotting*/
	
	plot_obstacle((UINT32 *)Physbase(), 200, 120, 100, 16, 400, 2);
	plot_obstacle((UINT32 *)Physbase(), 400, 150, 100, 16, 400, 2);

	/* TRIANGLE BORDER BITMAPS */
	plot_triangle_border((UINT32 *)base, top_triangle_bitmap, bottom_triangle_bitmap);
	/*plot_bitmap_16((UINT16 *)base, 0, 50, top_triangle_bitmap, HEIGHT_16);
	plot_bitmap_16((UINT16 *)base, 0, 330, bottom_triangle_bitmap, HEIGHT_16);*/
	/*plot_bitmap_32((UINT32 *)base, 0, 50, top_triangle_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 0, 314, bottom_triangle_bitmap, HEIGHT_32); Will eventuall just call plot_triangle_borders(); to loop.*/
	
	/* DINOSAUR BITMAPS */
	plot_bitmap_32((UINT32 *)base, 0, 184, dino_wdown_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 32, 184, dino_wup_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 64, 184, dino_dead_bitmap, HEIGHT_32);

	/* NUMBER BITMAPS */
	plot_bitmap_32((UINT32 *)base, 311, 359, zero_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 343, 359, one_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 375, 359, two_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 407, 359, three_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 439, 359, four_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 471, 359, five_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 503, 359, six_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 535, 359, seven_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 567, 359, eight_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 599, 359, nine_bitmap, HEIGHT_32);

	/* OBSTACLE EDGE BITMAPS */
	plot_bitmap_32((UINT32 *)base, 407, 168, obs_bottom_edge_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 407, 248, obs_top_edge_bitmap, HEIGHT_32);

	Cconin();

	return 0;
}