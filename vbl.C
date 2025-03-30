#include "vbl.h"

	
#include "IKBD.h"
void handle_VBL() {
	
	if (update_music(music_ticks)){
		
	}

	
}
void disable_ikbd_interrupts() {
    long old_ssp = Super(0);
    *IE &= 0xBF; /* interupt enable*/
    Super(old_ssp);
}

void enable_ikbd_interrupts() {
    long old_ssp = Super(0);
    *IE |= 0x40;
    Super(old_ssp);
}

void handle_IKBD(){

}

Vector install_vector(int num, Vector vector) {
	Vector original_vector;
	Vector *vectptr = (Vector *)((long)num << 2);
	long old_ssp = Super(0);
    
	original_vector = *vectp;
	*vectptr = vector;
	
    Super(old_ssp);
    
	return original_vector;
}

void install_vectors() {
    mask_interrupts();
	VBL_orig_vector = install_vector(VBL_ISR, vbl_isr);
    IKBD_orig_vector = install_vector(IKBD_ISR, ikbd_isr);
	unmask_interrupts();
}

void remove_vectors() {
    mask_interrupts();

	install_vector(VBL_ISR, VBL_orig_vector);
    install_vector(IKBD_ISR, IKBD_orig_vector);
	
	unmask_interrupts();
}
