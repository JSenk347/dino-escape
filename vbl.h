#ifndef VBL_H
#define VBL_H
#include <osbind.h>
#include "types.h"
#include "ISR.H"
#define VBL_ISR  28
#define IKBD_ISR 70

/* Pointers to hardware registers for IKBD and MFP */

typedef void (*Vector)();


extern Vector VBL_orig_vector;
extern Vector IKBD_orig_vector;

extern UINT8 head;
extern UINT8 tail;

extern UINT8 IKBD_buffer[256];

extern int music_ticks;
extern int score_ticks;
extern int enemy_ticks;
extern int key_update_ticks;
extern int render_request;
extern int mseX;
extern int mseY;
extern int mse_click;
extern int mse_enable;
extern bool key_repeat;
extern int seconds;
Vector install_vector(int num, Vector vector);
void remove_vectors();
void mask_interrupts();
void unmask_interrupts();
long kbd_read_char(bool update_head);
bool kbd_is_waiting();
void clear_kbd_buffer();
void do_VBL_ISR();
void do_IKBD_ISR();


#endif