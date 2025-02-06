#include "raster.h"
#include "bitmaps.h"
#include <stdio.h>
#include <osbind.h> 
#include <linea.h>

#define XOR 2
#define AND 3

int main(){
	int i;
	int y;

	void *base = Physbase();
	linea0();

	clear_screen((UINT16 *)base, 0);

	while (!Cconis()){
		plot_hline(y, XOR);
		Vsync();
		plot_hline(y,XOR);

		y++;

		if (y == 400)
			y = 0;
	}
	
	
	for (i = 0; i < 25; i++){
		/*plot_bitmap_16(base, 480, 16 * i, dino_wup_bitmap, HEIGHT_32);*/
		plot_bitmap_32((UINT32 *)base, 160, 32 * i, dino_wup_bitmap, HEIGHT_32);
	}

	return 0;
}