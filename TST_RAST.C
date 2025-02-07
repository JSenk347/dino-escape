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
	plot_gline(0, 0, 639, 399, XOR);
	plot_hline(200, XOR);
	plot_vline(320, XOR);
	plot_borders();
	

	/* DINOSAUR BITMAPS */
	plot_bitmap_32((UINT32 *)base, 0, 184, dino_wdown_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 32, 184, dino_wup_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 64, 184, dino_dead_bitmap, HEIGHT_32);

	/* NUMBER BITMAPS */
	plot_bitmap_32((UINT32 *)base, 96, 184, zero_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 128, 184, one_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 160, 184, two_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 192, 184, three_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 224, 184, four_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 256, 184, five_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 288, 184, six_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 320, 184, seven_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 352, 184, eight_bitmap, HEIGHT_32);
	plot_bitmap_32((UINT32 *)base, 384, 184, nine_bitmap, HEIGHT_32);

	Cconin();

	return 0;
}