#include "raster.h"

int main(){
	int i;

	void *base = Physbase();

	clear_screen(base, 0);
    
	for (i = 0; i < 25; i++){
		plot_bitmap_16(base, 480, 16 * i, s_bird_bitmap, S_BIRD_HEIGHT);
		plot_bitmap_32(base, 160, 32 * i, l_bird_bitmap, L_BIRD_HEIGHT);
	}

	return 0;
}