#include "vbl.h"
Vector VBL_orig_vector;
Vector IKBD_orig_vector;
UINT8 IKBD_buffer[256];
UINT8 head = 0;
UINT8 tail = 0;
unsigned char mse_button = 0xF8;
unsigned char mse_deltaX = 0x00;
unsigned char mse_deltaY = 0x00;
int mse_state = 0;
int render_mouse = 0;
int mseX;
int mseY;
int old_mseX;
int old_mseY;
int mse_click;
int mse_enable;
bool key_repeat = 0;
int render_request = 0;

volatile   		unsigned char *const CTRL       = 0xFFFC00;
volatile const 	unsigned char *const STATUS		= 0xFFFC00;
volatile const 	unsigned char *const READER		= 0xFFFC02;
volatile		unsigned char *const MFP 		= 0xFFFA11; 
volatile		unsigned char *const IE			= 0xFFFA09; 
char *ascii_tbl = 0xFFFE829C;


void mask_interrupts() {
    long old_ssp = Super(0);
    *IE &= 0xBF;
    Super(old_ssp);
}

void unmask_interrupts() {
    long old_ssp = Super(0);
    *IE |= 0x40;
    Super(old_ssp);
}
void do_VBL_ISR() {
	static int time;
	time++;

	if(time == 70) {
		time = 0;
		seconds++;
	}

	return;
}

void do_IKBD_ISR() {
    UINT8 code = *(READER);  /* Read byte from IKBD data register */

    
    if (code == 0x11 || code == 0x1F || code == 0x10) {
        /* W (0x11), S (0x1F), Q (0x10) pressed */
        IKBD_buffer[tail++] = code;
        key_repeat = 1;
    }
    else if (code == 0x91 || code == 0x9F || code == 0x90) {
        /* W, S, or Q released (break codes) */
        key_repeat = 0;
    }

    /* Clear bit 6 in MFP in-service register to acknowledge interrupt */
    *MFP &= 0xBF;
}

Vector install_vector(int num, Vector vector) {
	Vector original_vector;
	Vector *vectptr = (Vector *)((long)num << 2);
	long old_ssp = Super(0);
    
	original_vector = *vectptr;
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

long kbd_read_char(bool update_head) {
	long ret;
    
	mask_interrupts();
	
    /* read the scancode from buffer, and then put ascii value */
	ret = IKBD_buffer[head];
	ret = ret << 16;
	ret = ret + *(ascii_tbl + IKBD_buffer[head]);
	
	unmask_interrupts();
    
	if(update_head) {
		head++;
	}
	
	return ret;
}


/* 
Purpose: Checks to see if buffer is empty
Return: true = not empty
        false = empty
*/
bool kbd_is_waiting() {
	return head != tail;
}


/* 
Purpose: Empty the buffer
*/
void clear_kbd_buffer() {
    /* Keep going until buffer is empty */
	while(kbd_is_waiting()) {
		head++;
	}
    
    /* Clear the last value */
	IKBD_buffer[tail] = 0x00;
}