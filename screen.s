        xdef	set_video_base


set_video_base:
        link    a6, #0              ; Set up stack frame
        movem.l d0-d3/a0-a3, -(sp)        ; Save registers

        unlk    a6                  ; Restore frame
        rts                         ; Return to C


;-------------------------------------------

og_ssp:	ds.l	1


