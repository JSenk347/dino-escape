	xdef	_custom_vbl_isr
	xdef 	_custom_ikbd_isr

	xref	_handle_VBL
	xref 	_handle_IKBD

_custom_ikbd_isr:
	movem.l d0-2/a0-2,-(sp)
	jsr _handle_IKBD
	movem.l (sp)+,d0-2/a0-2
	rte

_custom_vbl_isr:
	movem.l d0-2/a0-2,-(sp)
	jsr _handle_VBL
	movem.l (sp)+,d0-2/a0-2
	rte
void custom_ikbd_isr();
void custom_vbl_isr();