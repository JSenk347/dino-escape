/*******************************************************************************
 AUTHORS: Anna Running Rabbit, Jordan Senko, Joseph Mills
 COURSE: COMP2659-001
 INSTRUCTOR: Tim Reimer
 DATE: Feb.10, 2025

 SUMMARY: Contains all game bitmaps
*******************************************************************************/
#include "raster.h"

const UINT32 white_bitmap [HEIGHT_32] = {
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000
};
const UINT32 black_bitmap[HEIGHT_32] = {
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF
};

/*******************************************************************************
	32x32 pixel bitmap for the player dino in the wings up position.
*******************************************************************************/
const UINT32 dino_wup_bitmap[HEIGHT_32] =
{
	0xFC00000F,
	0xFC00000F,
	0xC3C00033,
	0xC3C00033,
	0xC0303FC3,
	0xC0303FC3,
	0x33CC0C03,
	0x33CC0C03,
	0x3033303C,
	0x3033303C,
	0x0C33330C,
	0x0C33330C,
	0x030CF30F,
	0x030CF30F,
	0x00CC0003,
	0x00CC0003,
	0x003000FF,
	0x003000FF,
	0x00C00F00,
	0x00C00F00,
	0x03000C00,
	0x03000C00,
	0x0C003000,
	0x0C003000,
	0x0300C000,
	0x0300C000,
	0x03FF0000,
	0x03FF0000,
	0x0CCC0000,
	0x0CCC0000,
	0x03300000,
	0x03300000
};

/*******************************************************************************
	32x32 pixel bitmap for the player dino in the wings down position.
*******************************************************************************/
const UINT32 dino_wdown_bitmap[HEIGHT_32] = {
    0x3FC0,
	0x3FC0,
	0x0CC0,
	0x0CC0,
	0x303C,
	0x303C,
	0x330C,
	0x330C,
	0x3F30F,
	0x3F30F,
	0xC0003,
	0xC0003,
	0x3300FF,
	0x3300FF,
	0xC30F00,
	0xC30F00,
	0x3030F00,
	0x3030F00,
	0xC033300,
	0xC033300,
	0xC03F300,
	0xC03F300,
	0x300F0C00,
	0x300F0C00,
	0x300C0C00,
	0x303C3000,
	0x303C3000,
	0xC3CCC000,
	0xC3CCC000,
	0xFC030000,
	0xFC030000
};

/*******************************************************************************
	32x32 pixel bitmap for the player dino in the dead position.
*******************************************************************************/
const UINT32 dino_dead_bitmap[HEIGHT_32] =
{
	0x03300000,
	0x03300000,
	0x0CCC0000,
	0x0CCC0000,
	0x03FF0000,
	0x03FF0000,
	0x0300C000,
	0x0300C000,
	0x0C003000,
	0x0C003000,
	0x03000C00,
	0x03000C00,
	0x00C00F00,
	0x00C00F00,
	0x003000FF,
	0x003000FF,
	0x00CC0003,
	0x00CC0003,
	0x030CF3CF,
	0x030CF3CF,
	0x0C33300C,
	0x0C33300C,
	0x3033303C,
	0x3033303C,
	0x33CC0CC3,
	0x33CC0CC3,
	0xC0303FC3,
	0xC0303FC3,
	0xC3C00033,
	0xC3C00033,
	0xFC00000F,
	0xFC00000F
};

/*******************************************************************************
	32x32 pixel bitmap for the score digit 0.
*******************************************************************************/
const UINT32 zero_bitmap[HEIGHT_32] =
{
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0x81FFFE07,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF
};

/*******************************************************************************
	32x32 pixel bitmap for the score digit 1.
*******************************************************************************/
const UINT32 one_bitmap[HEIGHT_32] =
{
	0xFFFE01FF,
	0xFFFE01FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFE0001FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF,
	0xFFFE01FF
};

/*******************************************************************************
 	32x32 pixel bitmap for the score digit 22.
*******************************************************************************/
const UINT32 two_bitmap[HEIGHT_32] =
{
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFC00003F,
	0xFC00003F,
	0xFC00003F,
	0xFC00003F,
	0xFC00003F,
	0xFC00003F,
	0xC000003F,
	0xC000003F,
	0xC03FFFFF,
	0xC03FFFFF,
	0xC03FFFFF,
	0xC03FFFFF,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
};

/*******************************************************************************
 	32x32 pixel bitmap for the score digit 3.
*******************************************************************************/
const UINT32 three_bitmap[HEIGHT_32] =
{
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xFFFFFC0F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F
};

/*******************************************************************************
	32x32 pixel bitmap for the score digit 4.
*******************************************************************************/
const UINT32 four_bitmap[HEIGHT_32] =
{
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0XC000000F,
	0XC000000F,
	0XC000000F,
	0XC000000F,
	0XC000000F,
	0XC000000F,
	0XC000000F,
	0XC000000F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
};

/*******************************************************************************
	32x32 pixel bitmap for the score digit 5.
*******************************************************************************/
const UINT32 five_bitmap[HEIGHT_32] =
{
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC03FFFFF,
	0xC03FFFFF,
	0xC03FFFFF,
	0xC03FFFFF,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
};

/*******************************************************************************
	32x32 pixel bitmap for the score digit 6.
*******************************************************************************/
const UINT32 six_bitmap[HEIGHT_32] =
{
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC03FFFFF,
	0xC03FFFFF,
	0xC03FFFFF,
	0xC03FFFFF,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC03FF00F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
};

/*******************************************************************************
	32x32 pixel bitmap for the score digit 7.
*******************************************************************************/
const UINT32 seven_bitmap[HEIGHT_32] =
{
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF,
	0xFFF00FFF
};

/*******************************************************************************
	32x32 pixel bitmap for the score digit 8.
*******************************************************************************/
const UINT32 eight_bitmap[HEIGHT_32] =
{
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F
};

/*******************************************************************************
	32x32 pixel bitmap for the score digit 9.
*******************************************************************************/
const UINT32 nine_bitmap[HEIGHT_32] =
{
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC0FFFC0F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
	0xFFFFF00F,
};

/*******************************************************************************
	32x32 pixel bitmap for the upside down triangle (stalactites) for the
		gameplay screen top border.
*******************************************************************************/
const UINT32 top_triangle_bitmap[HEIGHT_32] =
{
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0x3FFFFFFC,
	0x3FFFFFFC,
	0x3FFFFFFC,
	0x3FFFFFFC,
	0x0FFFFFF0,
	0x0FFFFFF0,
	0x0FFFFFF0,
	0x0FFFFFF0,
	0x03FFFFC0,
	0x03FFFFC0,
	0x03FFFFC0,
	0x03FFFFC0,
	0x00FFFF00,
	0x00FFFF00,
	0x00FFFF00,
	0x00FFFF00,
	0x003FFC00,
	0x003FFC00,
	0x003FFC00,
	0x003FFC00,
	0x000FF000,
	0x000FF000,
	0x000FF000,
	0x000FF000,
	0x0003C000,
	0x0003C000,
	0x0003C000,
	0x0003C000
};

/*******************************************************************************
	32x32 pixel bitmap for the triangle (stalagmites) for the gameplay screen
		bottom border.
*******************************************************************************/
const UINT32 bottom_triangle_bitmap[HEIGHT_32] =
{
	0x0003C000,
	0x0003C000,
	0x0003C000,
	0x0003C000,
	0x000FF000,
	0x000FF000,
	0x000FF000,
	0x000FF000,
	0x003FFC00,
	0x003FFC00,
	0x003FFC00,
	0x003FFC00,
	0x00FFFF00,
	0x00FFFF00,
	0x00FFFF00,
	0x00FFFF00,
	0x03FFFFC0,
	0x03FFFFC0,
	0x03FFFFC0,
	0x03FFFFC0,
	0x0FFFFFF0,
	0x0FFFFFF0,
	0x0FFFFFF0,
	0x0FFFFFF0,
	0x3FFFFFFC,
	0x3FFFFFFC,
	0x3FFFFFFC,
	0x3FFFFFFC,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xFFFFFFFF
};

/*******************************************************************************
	32x32 pixel bitmap for the top left corner of the start button.
*******************************************************************************/
const UINT32 lt_top_start_bitmap[HEIGHT_32] =
{
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC000001F,
	0xC000001F,
	0xC0000018,
	0xC0000018,
	0xC0000018,
	0xC0000018,
	0xC000001F,
	0xC000001F,
	0xC0000018
};
/*const UINT32 lt_top_start_bitmap[HEIGHT_32] =
{
	0xFFFFFFFF,
	0xFFFFFFFF,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC003F0FC,
	0xC003F0FC,
	0xC0030CC3,
	0xC0030CC3,
	0xC003F0FC,
	0xC003F0FC,
	0xC00300CC,
	0xC00300CC,
	0xC00300C3,
	0xC00300C3,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000
};*/

/*******************************************************************************
	32x32 pixel bitmap for the top middle-left corner of the start button.
*******************************************************************************/
const UINT32 mid_lt_top_start_bitmap[HEIGHT_32] =
{
	0xFFFFFFFF,
	0xFFFFFFFF,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00FF00C3,
	0x00FF00C3,
	0x00C0C0C3,
	0x00C0C0C3,
	0x00C030C3,
	0x00C030C3,
	0x00C030C3,
	0x00C030C3,
	0x00C030C3,
	0x00C030C3,
	0x00C0C0C3,
	0x00C0C0C3,
	0x00FF00C3,
	0x00FF00C3,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0xF87FE1FE,
	0xF87FE1FE,
	0x01800601,
	0x01800601,
	0x01800600,
	0x01800600,
	0xE07F8600,
	0xE07F8600,
	0x00006600
	/*0xFFFFFFFF,
	0xFFFFFFFF,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x3FC3F0FC,
	0x3FC3F0FC,
	0x300C0300,
	0x300C0300,
	0x3F03C0F0,
	0x3F03C0F0,
	0x3000300C,
	0x3000300C,
	0x3FCFC3F0,
	0x3FCFC3F0,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000*/
};

/*******************************************************************************
	32x32 pixel bitmap for the top middle-right corner of the start button.
*******************************************************************************/
const UINT32 mid_rt_top_start_bitmap[HEIGHT_32] =
{
	0xFFFFFFFF,
	0xFFFFFFFF,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00C0F000,
	0x00C0F000,
	0xC0C30C00,
	0xC0C30C00,
	0x30CC0300,
	0x30CC0300,
	0x0CCC0300,
	0x0CCC0300,
	0x0CCC0300,
	0x0CCC0300,
	0x03C30C00,
	0x03C30C00,
	0x00C0F000,
	0x00C0F000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x07E1FE1F,
	0x07E1FE1F,
	0x98198198,
	0x98198198,
	0x18198198,
	0x18198198,
	0x1819FE1F,
	0x1819FE1F,
	0x1FF98018
	
	/*0xFFFFFFFF,
	0xFFFFFFFF,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0FF30CFF,
	0x0FF30CFF,
	0x0C03CC0C,
	0x0C03CC0C,
	0x0FC33C0C,
	0x0FC33C0C,
	0x0C030C0C,
	0x0C030C0C,
	0x0FF30C0C,
	0x0FF30C0C,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000*/
};

/*******************************************************************************
	32x32 pixel bitmap for the top right corner of the start button.
*******************************************************************************/
const UINT32 rt_top_start_bitmap[HEIGHT_32] =
{
	0xFFFFFFFF,
	0xFFFFFFFF,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0xF8000003,
	0xF8000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0xE0000003,
	0xE0000003,
	0x00000003
	
	/*0xFFFFFFFF,
	0xFFFFFFFF,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0xCFF3F003,
	0xCFF3F003,
	0x0C030C03,
	0x0C030C03,
	0x0FC3F003,
	0x0FC3F003,
	0x0C033003,
	0x0C033003,
	0x0FF30C03,
	0x0FF30C03,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003*/
};

/*******************************************************************************
	32x32 pixel bitmap for the bottom left corner of the start button.
*******************************************************************************/
const UINT32 lt_bottom_start_bitmap[HEIGHT_32] =
{
	0xC0000018,
	0xC0000018,
	0xC0000018,
	0xC000001F,
	0xC000001F,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0FFFFFF,
	0xC0FFFFFF,
	0xC0C00000,
	0xC0C7EFF1,
	0xC0C7EFF1,
	0xC0D80186,
	0xC0D80186,
	0xC0C78187,
	0xC0C78187,
	0xC0C06186,
	0xC0C06186,
	0xC0DF8186,
	0xC0DF8186,
	0xC0C00000,
	0xC0FFFFFF,
	0xC0FFFFFF,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xFFFFFFFF,
	0xFFFFFFFF
};
/*const UINT32 lt_bottom_start_bitmap[HEIGHT_32] =
{
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC00000FF,
	0xC00000FF,
	0xC000000C,
	0xC000000C,
	0xC000000C,
	0xC000000C,
	0xC000000C,
	0xC000000C,
	0xC000000C,
	0xC000000C,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xC0000000,
	0xFFFFFFFF,
	0xFFFFFFFF
};*/

/*******************************************************************************
	32x32 pixel bitmap for the bottom middle-left corner of the start button.
*******************************************************************************/
const UINT32 mid_lt_bottom_start_bitmap[HEIGHT_32] =
{
	0x00006600,
	0x00006601,
	0x00006601,
	0xF9FFE1FE,
	0xF9FFE1FE,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0xFFFFFFC0,
	0xFFFFFFC0,
	0x000000C0,
	0xE3F1FEC0,
	0xE3F1FEC0,
	0x1B0C30C0,
	0x1B0C30C0,
	0xFBF030C0,
	0xFBF030C0,
	0x1B3030C0,
	0x1B3030C0,
	0x1B0C30C0,
	0x1B0C30C0,
	0x000000C0,
	0xFFFFFFC0,
	0xFFFFFFC0,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0xFFFFFFFF,
	0xFFFFFFFF

	/*0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0xC3C003F3,
	0xC3C003F3,
	0x0C300C00,
	0x0C300C00,
	0x0C3003C0,
	0x0C3003C0,
	0x0C300030,
	0x0C300030,
	0x03C00FC0,
	0x03C00FC0,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0xFFFFFFFF,
	0xFFFFFFFF*/
};

/*******************************************************************************
	32x32 pixel bitmap for the bottom middle-right corner of the start button.
*******************************************************************************/
const UINT32 mid_rt_bottom_start_bitmap[HEIGHT_32] =
{
	0x18198018,
	0x98198018,
	0x98198018,
	0x1819801F,
	0x1819801F,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x0001FFFF,
	0x0001FFFF,
	0x00018000,
	0x00018F18,
	0x00018F18,
	0x0001B0D8,
	0x0001B0D8,
	0x0001B0D8,
	0x0001B0D8,
	0x0001B318,
	0x0001B318,
	0x00018CC7,
	0x00018CC7,
	0x00018000,
	0x0001FFFF,
	0x0001FFFF,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0xFFFFFFFF,
	0xFFFFFFFF
	
	/*0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0xFF0F0FC3,
	0xFF0F0FC3,
	0x3030CC30,
	0x3030CC30,
	0x303FCFC0,
	0x303FCFC0,
	0x3030CCC0,
	0x3030CCC0,
	0x3030CC30,
	0x3030CC30,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0x00000000,
	0xFFFFFFFF,
	0xFFFFFFFF*/
};

/*******************************************************************************
	32x32 pixel bitmap for the bottom right corner of the start button.
*******************************************************************************/
const UINT32 rt_bottom_start_bitmap[HEIGHT_32] =
{
	0x00000003,
	0x00000003,
	0x00000003,
	0xF8000003,
	0xF8000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0xFFFFFF03,
	0xFFFFFF03,
	0x00000303,
	0x6187FB03,
	0x6187FB03,
	0x6180C303,
	0x6180C303,
	0x6180C303,
	0x6180C303,
	0x6180C303,
	0x6180C303,
	0x8180C303,
	0x8180C303,
	0x00000303,
	0xFFFFFF03,
	0xFFFFFF03,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0xFFFFFFFF,
	0xFFFFFFFF

	/*0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0xFF000003,
	0xFF000003,
	0x30000003,
	0x30000003,
	0x30000003,
	0x30000003,
	0x30000003,
	0x30000003,
	0x30000003,
	0x30000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0x00000003,
	0xFFFFFFFF,
	0xFFFFFFFF*/
};

/*******************************************************************************
	32x32 pixel bitmap for the bottom edge of the top portion of the obstacle.
*******************************************************************************/
const UINT32 obs_bottom_edge_bitmap[HEIGHT_32] =
{
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC000000F,
	0xC000000F,
	0xC000003C,
	0xC000003C,
	0xC0000FF0,
	0xC0000FF0,
	0xF0003C00,
	0xF0003C00,
	0x3FF03000,
	0x3FF03000,
	0x003CF000,
	0x003CF000,
	0x000FC000,
	0x000FC000
};

/*******************************************************************************
	32x32 pixel bitmap for the top edge of the bottom portion of the obstacle.
*******************************************************************************/
const UINT32 obs_top_edge_bitmap[HEIGHT_32] =
{
	0x03FC0000,
	0x03FC0000,
	0x0F0FF000,
	0x0F0FF000,
	0x0C003FF0,
	0x0C003FF0,
	0x0C00003C,
	0x0C00003C,
	0x0C00000F,
	0x0C00000F,
	0x3C000003,
	0x3C000003,
	0x30000003,
	0x30000003,
	0x30000003,
	0x30000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003,
	0xC0000003	
};

/*******************************************************************************
	32x32 pixel bitmap for straight portion of the obstacle.
*******************************************************************************/
const UINT32 obs_bitmap[HEIGHT_32] =
{
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003,
    0xC0000003
};