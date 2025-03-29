#ifndef VBL_H
#define VBL_H
#include <osbind.h>
#include "types.h"
int music_ticks = 0;
int score_ticks = 0;
int enemy_ticks = 0;
int render_request = 1; 
/* Pointers to hardware registers for IKBD and MFP */
volatile unsigned char *const IKBD_CTRL = (unsigned char *)0xFFFC00;       /* Control register (write) */
volatile const unsigned char *const IKBD_STATUS = (unsigned char *)0xFFFC00; /* Status register (read) */
volatile const unsigned char *const IKBD_DATA = (unsigned char *)0xFFFC02;   /* Data register (read) */
volatile unsigned char *const MFP_IN_SERVICE_B = (unsigned char *)0xFFFA11;  /* MFP in-service register */
volatile unsigned char *const MFP_IEB = (unsigned char *)0xFFFA09;           /* MFP interrupt enable register */
typedef void (*Vector)(); 
int render_request = 0;
Vector install_vector(int num, Vector vector);
void remove_vectors();
void mask_interrupts();
void unmask_interrupts();

#endif