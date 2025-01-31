#include "raster.h"
#include "bitmaps.h"
#include <osbind.h>

int main(){
	int i;

	void *base = Physbase();

	clear_screen((UINT16 *)base, 0);
    
	for (i = 0; i < 25; i++){
		/*plot_bitmap_16(base, 480, 16 * i, dino_wup_bitmap, HEIGHT_32);*/
		plot_bitmap_32((UINT32 *)base, 160, 32 * i, dino_wup_bitmap, HEIGHT_32);
	}

	return 0;
}