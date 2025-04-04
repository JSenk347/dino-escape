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
int render_request = 1;
volatile   		unsigned char *const CTRL       = 0xFFFC00;
volatile const 	unsigned char *const STATUS		= 0xFFFC00;
volatile const 	unsigned char *const READER		= 0xFFFC02;
volatile		unsigned char *const MFP 		= 0xFFFA11; 
volatile		unsigned char *const IE			= 0xFFFA09; 

void handle_VBL() {
	
	if (mse_enable == 1) {
		render_mouse = 1;
	}
	
	render_request = 1;
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

void handle_IKBD() {
    UINT8 code = *(READER);  /* Read byte from IKBD data register */

    if (mse_state == 0) {
        if (code >= 0xF8) {
            /* Start of a mouse packet (header byte with button state) */
            mse_button = code;
            mse_state = 1;  /* Next byte will be delta X */
        }
        else if (code == 0x11 || code == 0x1F || code == 0x10) {
            /* W (0x11), S (0x1F), Q (0x10) pressed */
            IKBD_buffer[tail++] = code;  /* Store key in buffer */
            key_repeat = 1;           /* Enable key repeat */
        }
        else if (code == 0x91 || code == 0x9F || code == 0x90) {
            /* W, S, or Q released (break codes) */
            key_repeat = 0;          /* Disable key repeat */
        }
    }
    else if (mse_state == 1) {
        /* Second byte of mouse packet: delta X */
        mse_deltaX = code;
        mse_state = 2;  /* Next byte will be delta Y */
    }
    else if (mse_state == 2) {
        /* Third byte of mouse packet: delta Y */
        mse_deltaY = code;
        mse_state = 0;  /* Mouse packet complete */
    }
    else {
        /* Safety reset in case of unexpected state */
        mse_state = 0;
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
    enable_ikbd_interrupts();
	VBL_orig_vector = install_vector(VBL_ISR, vbl_isr);
    IKBD_orig_vector = install_vector(IKBD_ISR, ikbd_isr
	);
	disable_ikbd_interrupts();
}

void remove_vectors() {
    enable_ikbd_interrupts();

	install_vector(VBL_ISR, VBL_orig_vector);
    install_vector(IKBD_ISR, IKBD_orig_vector);
	
	disable_ikbd_interrupts();
}

