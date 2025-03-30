;-------------------------------------------------------------
; AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
; COURSE: COMP2659-001
; INSTRUCTOR: Tim Reimer
; DATE: Mar.28, 2025

; FILE: Screen.s
; SUMMARY: Contains the functions to set video base
;-------------------------------------------------------------
        xdef	_set_video_base
OFFSET  equ     8
_set_video_base:
        link    a6,#0                  ; Set up stack frame
        movem.l d0-d3/a0-a3,-(sp)      ; Save registers

        ; Enter supervisor mode
        clr.l   d0                      ; Push 0 (means "enter supervisor mode")
        move.l  d0,-(sp)
        clr.l   -(sp)
        move.w  #$20,-(sp)             ; Super() function code
        trap    #1
        addq.l  #6,sp                  ; Clean up trap call
        move.l  d0,og_ssp

        move.l  OFFSET(a6),d0           
        lsr.l   #8,d0
        lea	$FFFF8201,a0	
	movep.w	d0,0(a0)

        ; Leave supervisor mode
        move.l  d0,-(sp)
        move.l  (og_ssp),-(sp)
        move.w  #$20,-(sp)
        trap    #1                      ; Leave supervisor mode
        addq.l  #6,sp
        move.l	(sp)+,d0
        unlk    a6                      ; Restore frame
        rts                             ; Return to C
;-------------------------------------------

og_ssp:	ds.l	1



