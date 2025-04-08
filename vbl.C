#include "vbl.h"
Vector VBL_orig_vector;
Vector IKBD_orig_vector;
Scale scale;
Song song;
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

volatile   		unsigned char *const CTRL       = 0xFFFC00;
volatile const 	unsigned char *const STATUS		= 0xFFFC00;
volatile const 	unsigned char *const READER		= 0xFFFC02;
volatile		unsigned char *const MFP 		= 0xFFFA11; 
volatile		unsigned char *const IE			= 0xFFFA09; 
char *ascii_tbl = 0xFFFE829C;


void mask_interrupts() {
    long old_ssp;
    UINT32 supercheck = Super(1);  
    if (!supercheck) {
        old_ssp = Super(0);
    }
    *IE &= 0xBF;
    if (!supercheck) {
        Super(old_ssp);
    }
}

void unmask_interrupts() {
    long old_ssp;
    UINT32 supercheck = Super(1);  
    if (!supercheck) {
        old_ssp = Super(0);
    }
    *IE |= 0x40;
    if (!supercheck) {
        Super(old_ssp);
    }
}
void do_VBL_ISR() {
	static int time;
    mseX += (int)((char)mse_deltaX);
    mseY += (int)((char)mse_deltaY);

   
    if (mseX < 0) mseX = 0;
    if (mseX > 628) mseX = 628;
    if (mseY < 0) mseY = 0;
    if (mseY > 378) mseY = 378;

    mse_deltaX = 0;
    mse_deltaY = 0;

    if (mse_button == 0xF8) mse_click = 0;
    else if (mse_button == 0xF9) mse_click = 1;
    else if (mse_button == 0xFA) mse_click = 2;
    else if (mse_button == 0xFB) mse_click = 3;

	time++;
    render_request = 1;
    render_mouse = 1;  
    ticks+= 10;
	if(time == 70) {
		time = 0;
		seconds++;
	}
	return;
}

void do_IKBD_ISR() {
    UINT8 code = *(READER);  

    if (mse_state == 0) {
        if (code >= 0xF8) {          
            mse_button = code;
            mse_state = 1;
        } else if ((code & 0x80) == 0) {  
            IKBD_buffer[tail++] = code;
            key_repeat = 1;
        } else if ((code & 0x80) == 0x80) { 
            key_repeat = 0;
        }
    } else if (mse_state == 1) {
        mse_deltaX = code;
        mse_state = 2;
    } else if (mse_state == 2) {
        mse_deltaY = code;
        mse_state = 0;
    }
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
/*
Purpose: Initialize mouse settings, and draw it 
*/
void init_mouse(UINT32 *base) {
	mseX = 320;
	mseY = 200;
	
	old_mseX = mseX;
	old_mseY = mseY;
	
	mse_click = 0;
	
	save_mouse_bkgd(base, mseX, mseY); 
	plot_mouse((UINT16 *)base, mseX, mseY, mouse_cursor);
}
void update_mouse(UINT32 *base) {
	
    /* Set new mouse values */
	mseX += (int)((char)mse_deltaX);
	mseY += (int)((char)mse_deltaY);

    /* Check for screen bounds */
	if(mseX < 0) {
		mseX = 0;
	}
	else if(mseX > 628) {
		mseX = 628;
	}
	
	if(mseY < 0) {
		mseY = 0;
	}
	else if(mseY > 378) {
		mseY = 378;
	}

	mse_deltaX = 0;
	mse_deltaY = 0;
		

    /* Set mouse click values */
    if(mse_button == 0xF8) {
		mse_click = 0;
	}
	else if(mse_button == 0xF9) {
		mse_click = 1;
	}
	else if(mse_button == 0xFA) {
		mse_click = 2;
	}
    else if(mse_button == 0xFB) {
		mse_click = 3;
	}

    /* If requested to render mouse, then draw it. Hooked up to vbl timer */
	if(render_mouse == 1) {
		restore_mouse_bkgd(base, old_mseX, old_mseY);
		save_mouse_bkgd(base, mseX, mseY);
		plot_mouse((UINT16 *)base, mseX, mseY, mouse_cursor);
		
		old_mseX = mseX;
		old_mseY = mseY;
		
		render_mouse = 0;
	}	
	
}
UINT8 mouse_inBounds() {
	UINT8 inBounds = 0;

	if ((mseX >= 260 && mseX <= 315) &&
		(mseY >= 205 && mseY <= 225)) {
		inBounds = 1; 
	}
	else if ((mseX >= 335 && mseX <= 365) &&
			 (mseY >= 205 && mseY <= 225)) {
		inBounds = 2;
	}

	return inBounds;
}