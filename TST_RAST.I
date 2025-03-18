# 1 "tst_rast.c" 1
# 1 "./raster.h" 1
# 12 "./raster.h"
typedef unsigned long UINT32;
typedef unsigned int UINT16;
typedef unsigned char UINT8;

void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, unsigned int height);
void clear_rect(UINT16 *base, int x, int y, int width, int height);
void overwrite_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void plot_bitmap_16(UINT16 *base, int x, int y,
        const UINT16 *bitmap, unsigned int height);
void clear_screen(UINT16 *base, int pattern);
void plot_hline(unsigned short y, short mode);
void plot_vline(unsigned short x, short mode);
void plot_gline(unsigned short x1, unsigned short y1,
                unsigned short x2, unsigned short y2,
                short mode, int set_bit);
void plot_top_obs(UINT32 *base, int x, int gap_y, int mode);
void plot_bottom_obs(UINT32 *base, int x, int gap_y, int mode);
void plot_obstacles(UINT32 *base, int x, int gap_y, int mode);
void plot_borders();
void plot_borders_raster();
void plot_top_start_button(UINT32 *base, const UINT32 *lt_top_start_bitmap,
	        const UINT32 *mid_lt_top_start_bitmap, const UINT32 *mid_rt_top_start_bitmap,
	        const UINT32 *rt_top_start_bitmap);
void plot_bottom_start_button(UINT32 *base, const UINT32 *lt_bottom_start_bitmap,
	        const UINT32 *mid_lt_bottom_start_bitmap, const UINT32 *mid_rt_bottom_start_bitmap,
	        const UINT32 *rt_bottom_start_bitmap);
void disable_cursor();
void clear_far_left(UINT32 *base);
void clear_region(UINT32 *base, int x, int y, unsigned int pattern);
void clear_cave_region(UINT32 *base);
# 7 "tst_rast.c" 2
# 1 "./bitmaps.h" 1
# 7 "./bitmaps.h"
extern const UINT32 white_bitmap[32 ];
extern const UINT32 black_bitmap[32 ];
extern const UINT32 dino_wup_bitmap[32 ];
extern const UINT32 dino_wdown_bitmap[32 ];
extern const UINT32 dino_dead_bitmap[32 ];
extern const UINT32 zero_bitmap[32 ];
extern const UINT32 one_bitmap[32 ];
extern const UINT32 two_bitmap[32 ];
extern const UINT32 three_bitmap[32 ];
extern const UINT32 four_bitmap[32 ];
extern const UINT32 five_bitmap[32 ];
extern const UINT32 six_bitmap[32 ];
extern const UINT32 seven_bitmap[32 ];
extern const UINT32 eight_bitmap[32 ];
extern const UINT32 nine_bitmap[32 ];
extern const UINT32 top_triangle_bitmap[32 ];
extern const UINT32 bottom_triangle_bitmap[32 ];
extern const UINT32 lt_top_start_bitmap[32 ];
extern const UINT32 mid_lt_top_start_bitmap[32 ];
extern const UINT32 mid_rt_top_start_bitmap[32 ];
extern const UINT32 rt_top_start_bitmap[32 ];
extern const UINT32 lt_bottom_start_bitmap[32 ];
extern const UINT32 mid_lt_bottom_start_bitmap[32 ];
extern const UINT32 mid_rt_bottom_start_bitmap[32 ];
extern const UINT32 rt_bottom_start_bitmap[32 ];
extern const UINT32 obs_bottom_edge_bitmap[32 ];
extern const UINT32 obs_top_edge_bitmap[32 ];
extern const UINT32 obs_bitmap[32 ];
# 8 "tst_rast.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 11 "C:/c68/include/stdio.h" 2
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 10 "tst_rast.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 11 "tst_rast.c" 2
# 1 "C:/c68/include/linea.h" 1
# 325 "C:/c68/include/linea.h"
typedef struct {



   short  _VPLANES;
   short  _VWRAP;




   short  *_CONTRL;
   short  *_INTIN;
   short  *_PTSIN;
   short  *_INTOUT;
   short  *_PTSOUT;
# 349 "C:/c68/include/linea.h"
   short  _COLBIT0;
   short  _COLBIT1;
   short  _COLBIT2;
   short  _COLBIT3;




   short  _LSTLIN;



   short  _LNMASK;



   short  _WMODE;
# 372 "C:/c68/include/linea.h"
   short  _X1;

   short  _Y1;

   short  _X2;

   short  _Y2;


   short  *_PATPTR;

   short  _PATMSK;

   short  _MFILL;



   short  _CLIP;
   short  _XMINCL;
   short  _YMINCL;
   short  _XMAXCL;
   short  _YMAXCL;


   short  _XDDA;


   short  _DDAINC;



   short  _SCALDIR;
   short  _MONO;





   short  _SOURCEX;
# 417 "C:/c68/include/linea.h"
   short  _SOURCEY;

   short  _DESTX;
   short  _DESTY;
   short  _DELX;

   short  _DELY;

   short  *_FBASE;
   short  _FWIDTH;

   short  _STYLE;
# 435 "C:/c68/include/linea.h"
   short  _LITEMASK;

   short  _SKEWMASK;

   short  _WEIGHT;

   short  _ROFF;


   short  _LOFF;


   short  _SCALE;

   short  _CHUP;




   short  _TEXTFG;

   char  *_SCRTCHP;




   short  _SCRPT2;



   short  _TEXTBG;


   short  _COPYTRAN;
# 476 "C:/c68/include/linea.h"
 short(*_SEEDABORT) (void) ;
# 484 "C:/c68/include/linea.h"
} __LINEA;
# 546 "C:/c68/include/linea.h"
typedef struct _font {



   short  font_id;

   short  size;

   char   name[32];

   short  first_ade;


   short  last_ade;


   short  top;

   short  ascent;

   short  half;

   short  descent;

   short  bottom;



short max_char_width;

short max_cell_width;

  short left_offset;

  short right_offset;

   short  thicken;

   short  ul_size;

   short  lighten;

   short  skew;



   short  flags;





   char   *h_table;

   short  *off_table;

   char   *dat_table;

   short  form_width;

   short  form_height;

 struct _font *next_font;


} __FONT;
# 620 "C:/c68/include/linea.h"
typedef short(*FPTR) (void) ;
typedef FPTR *FUNCPTR;
# 628 "C:/c68/include/linea.h"
typedef struct {



   char   fg0bg0;
   char   fg0bg1;
   char   fg1bg0;
   char   fg1bg1;

} OP_TAB;





typedef struct  {
	short	bl_xmin;
	short	bl_ymin;
	char	*bl_form;
	short	bl_nxwd;
	short 	bl_nxln;
	short 	bl_nxpl;
}SDDB;
# 673 "C:/c68/include/linea.h"
typedef struct {



   short   bb_b_wd;
   short   bb_b_ht;
   short   bb_plane_ct;
   short   bb_fg_col;
   short   bb_bg_col;
   OP_TAB  bb_op_tab;
   SDDB	   bb_s;
   SDDB	   bb_d;
   short   *bb_p_addr;
   short   bb_p_nxln;
   short   bb_p_nxpl;
   short   bb_p_mask;
   char	   bb_fill[24];

} BBPB;
# 700 "C:/c68/include/linea.h"
typedef struct
{
	char		*fd_addr;


	short		fd_w;
	short		fd_h;
	short		fd_wdwidth;
	short		fd_stand;
	short		fd_nplanes;
	short		fd_r1;
	short		fd_r2;
	short		fd_r3;
} MFDB;
# 720 "C:/c68/include/linea.h"
typedef struct
{
	short	sp_xhot;
	short	sp_yhot;
	short	sp_format;
	short	sp_bg;
	short	sp_fg;
	short	sp_data[32];





} SFORM;
# 750 "C:/c68/include/linea.h"
extern __LINEA *__aline;



extern __FONT  **__fonts;



extern short  (**__funcs) (void) ;
# 1013 "C:/c68/include/linea.h"
 void linea0 (void) ;
 void linea1 (void) ;
 int linea2 (void) ;
 void linea3 (void) ;
 void linea4 (void) ;
 void linea5 (void) ;
 void linea6 (void) ;
 void linea7 (BBPB *P) ;
 void linea8 (void) ;
 void linea9 (void) ;
 void lineaa (void) ;
 void lineab (void) ;
 void lineac (void *P) ;
 void linead (int x, int y, SFORM *sd, void *ss) ;
 void lineae (void) ;
 void lineaf (void) ;
# 12 "tst_rast.c" 2
# 20 "tst_rast.c"
int main()
{
	void *base = (void*)_trap_14_w((short)0x2) ;
	linea0();

	disable_cursor();
	clear_screen((UINT16 *)base, 0);


	plot_borders_raster();


	plot_bitmap_32((UINT32 *)base, 16, 184, dino_wdown_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 48, 184, dino_wup_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 80, 184, dino_dead_bitmap, 32 );


	plot_bitmap_32((UINT32 *)base, 311, 359, zero_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 343, 359, one_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 375, 359, two_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 407, 359, three_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 439, 359, four_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 471, 359, five_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 503, 359, six_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 535, 359, seven_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 567, 359, eight_bitmap, 32 );
	plot_bitmap_32((UINT32 *)base, 599, 359, nine_bitmap, 32 );





	plot_obstacles((UINT32 *)base, 96, 279, 1);


	plot_top_start_button((UINT32 *)base, lt_top_start_bitmap,
			mid_lt_top_start_bitmap, mid_rt_top_start_bitmap,
			rt_top_start_bitmap);
	plot_bottom_start_button((UINT32 *)base, lt_bottom_start_bitmap,
			mid_lt_bottom_start_bitmap, mid_rt_bottom_start_bitmap,
			rt_bottom_start_bitmap);

	_trap_1_w((short)0x01) ;

	return 0;
}
