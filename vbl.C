#include "vbl.h"
Vector VBL_orig_vector;
Vector IKBD_orig_vector;
Scale scale;
Song song;
UINT8 IKBD_buffer[256];
UINT8 head = 0;
UINT8 tail = 0;
unsigned char mse_button = 0xF8;
unsigned char mse_baseX = 0x00;
unsigned char mse_baseY = 0x00;
int mse_state = 0;
int render_mouse = 0;
int mse_X;
int mse_Y;
int old_mse_X;
int old_mse_Y;
int mse_click;
int mse_enable;
bool key_repeat = 0;

volatile   		unsigned char *const CTRL       = 0xFFFC00;
volatile const 	unsigned char *const STATUS		= 0xFFFC00;
volatile const 	unsigned char *const READER		= 0xFFFC02;
volatile		unsigned char *const MFP 		= 0xFFFA11; 
volatile		unsigned char *const IE			= 0xFFFA09; 
char *ascii_tbl = 0xFFFE829C;

/*******************************************************************************
    PURPOSE: Masks the interrupts by setting the IE register to disable VBL and IKBD
			 interrupts. This is done by clearing the 6th bit of the IE.
    INPUT:  N/A 
    OUTPUT: N/A
*******************************************************************************/
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
/*******************************************************************************
    PURPOSE: Unmasks the interrupts by setting the IE register to allow VBL and IKBD
			 interrupts to be processed. This is done by setting the 6th bit of the IE.
    INPUT:  N/A 
    OUTPUT: N/A
*******************************************************************************/
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
/*******************************************************************************
    PURPOSE: do_VBL_ISR is the interrupt service routine for the VBL. It handles the
			 mouse and keyboard input. The function reads the scancode from the IKBD.
    INPUT:  N/A 
    OUTPUT: N/A
*******************************************************************************/
void do_VBL_ISR() {
	static int time;
    mse_X += (int)((char)mse_baseX);
    mse_Y += (int)((char)mse_baseY);

   
    if (mse_X < 0) mse_X = 0;
    if (mse_X > 628) mse_X = 628;
    if (mse_Y < 0) mse_Y = 0;
    if (mse_Y > 378) mse_Y = 378;

    mse_baseX = 0;
    mse_baseY = 0;

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
/*******************************************************************************
    PURPOSE: do_IKBD_ISR is the interrupt service routine for the IKBD. It handles
			 mouse and keyboard input. The function reads the scancode from the IKBD.
    INPUT:  N/A
    OUTPUT: N/A
*******************************************************************************/
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
        mse_baseX = code;
        mse_state = 2;
    } else if (mse_state == 2) {
        mse_baseY = code;
        mse_state = 0;
    }
    *MFP &= 0xBF;   
}
/*******************************************************************************
    PURPOSE: Installs the VBL and IKBD vectors by saving the original vectors and
			 replacing them with the new ones. The VBL vector is set to the vbl_isr.
    INPUT:  - num: the vector number to install
			- vector: the new vector to install 
    OUTPUT: N/A
*******************************************************************************/
Vector install_vector(int num, Vector vector) {
	Vector original_vector;
	Vector *vectptr = (Vector *)((long)num << 2);
	long old_ssp = Super(0);
    
	original_vector = *vectptr;
	*vectptr = vector;

	
    Super(old_ssp);
    
	return original_vector;
}
/*******************************************************************************
    PURPOSE: Installs the VBL and IKBD vectors by saving the original vectors and
			 replacing them with the new ones. The VBL vector is set to the vbl_isr.
    INPUT:  N/A 
    OUTPUT: N/A
*******************************************************************************/
void install_vectors() {
    mask_interrupts();
	VBL_orig_vector = install_vector(VBL_ISR, vbl_isr); 
    IKBD_orig_vector = install_vector(IKBD_ISR, ikbd_isr);   
	unmask_interrupts();
}
/*******************************************************************************
    PURPOSE: Removes the VBL and IKBD vectors by restoring the original vectors.
    INPUT:  N/A
    OUTPUT: N/A
*******************************************************************************/
void remove_vectors() {
    mask_interrupts();
	install_vector(VBL_ISR, VBL_orig_vector); 
    install_vector(IKBD_ISR, IKBD_orig_vector);   
	unmask_interrupts();
}
/*******************************************************************************
    PURPOSE: Keyboard buffer read function. Reads the scancode from the buffer and
			 converts it to an ASCII value using the ascii table.
    INPUT:  - update_head: boolean value to determine if the head should be updated
    OUTPUT: N/A
*******************************************************************************/
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


/*******************************************************************************
    PURPOSE: Keyboard buffer check. Returns true if the head is not equal to the tail.
			 This indicates that there is a character waiting in the buffer.
    INPUT:  N/A 
    OUTPUT: N/A
*******************************************************************************/
bool kbd_is_waiting() {
	return head != tail;
}


/*******************************************************************************
    PURPOSE: Clears the keyboard buffer by incrementing the head until it reaches the
			 tail. The last value is set to 0x00.
    INPUT:  N/A 
    OUTPUT: N/A
*******************************************************************************/
void clear_kbd_buffer() {
    /* Keep going until buffer is empty */
	while(kbd_is_waiting()) {
		head++;
	}
    
    /* Clear the last value */
	IKBD_buffer[tail] = 0x00;
}
/*******************************************************************************
    PURPOSE: Initializes the mouse by setting the initial position and saving the
			 background. The mouse is drawn to the screen at the end of the function.
    INPUT:  - Base pointer to the frame buffer
    OUTPUT: N/A
*******************************************************************************/
void init_mouse(UINT32 *base) {
	mse_X = 320;
	mse_Y = 200;
	
	old_mse_X = mse_X;
	old_mse_Y = mse_Y;
	
	mse_click = 0;
	
	save_mouse_bkgd(base, mse_X, mse_Y); 
	plot_mouse((UINT16 *)base, mse_X, mse_Y, mouse_cursor);
}
/*******************************************************************************
    PURPOSE: Update the mouse position and click values. The mouse is drawn to the
			 screen at the end of the function. 	
    INPUT:  N/A
    OUTPUT: N/A
*******************************************************************************/
void update_mouse(UINT32 *base) {
	
    /* Set new mouse values */
	mse_X += (int)((char)mse_baseX);
	mse_Y += (int)((char)mse_baseY);

    /* Check for screen bounds */
	if(mse_X < 0) {
		mse_X = 0;
	}
	else if(mse_X > 628) {
		mse_X = 628;
	}
	
	if(mse_Y < 0) {
		mse_Y = 0;
	}
	else if(mse_Y > 378) {
		mse_Y = 378;
	}

	mse_baseX = 0;
	mse_baseY = 0;
		

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
		restore_mouse_bkgd(base, old_mse_X, old_mse_Y);
		save_mouse_bkgd(base, mse_X, mse_Y);
		plot_mouse((UINT16 *)base, mse_X, mse_Y, mouse_cursor);
		
		old_mse_X = mse_X;
		old_mse_Y = mse_Y;
		
		render_mouse = 0;
	}	
	
}
/*******************************************************************************
    PURPOSE: Mouse inBounds function. Checks if the mouse is in the bounds of the
			 start or quit button. Returns 1 if in start button, 2 if in quit 
			 button, and 0 if not in either.
    INPUT:  N/A
    OUTPUT: N/A
*******************************************************************************/
UINT8 mouse_inBounds() {
	UINT8 inBounds = 0;

	if ((mse_X >= 260 && mse_X <= 315) &&
		(mse_Y >= 205 && mse_Y <= 225)) {
		inBounds = 1; 
	}
	else if ((mse_X >= 335 && mse_X <= 380) &&
			 (mse_Y >= 205 && mse_Y <= 225)) {
		inBounds = 2;
	}

	return inBounds;
}