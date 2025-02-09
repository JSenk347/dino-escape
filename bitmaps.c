#include "raster.h"

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
	0x0C33330C,
	0x0C33330C,
	0x3033303C,
	0x3033303C,
	0x33CC0C03,
	0x333C0C03,
	0xC0303FC3,
	0xC0303FC3,
	0xC3C00033,
	0xC3C00033,
	0xFC00000F,
	0xFC00000F
};

const UINT32 zero_bitmap[HEIGHT_32] =
{
	0xFF0001FF,
	0xFF0001FF,
	0xFF0001FF,
	0xFF0001FF,
	0xFF0001FF,
	0xFF0001FF,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0x00FFFE00,
	0xFF0001FF,
	0xFF0001FF,
	0xFF0001FF,
	0xFF0001FF,
	0xFF0001FF,
	0xFF0001FF
};

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

const UINT16 triangle_bitmap[HEIGHT_16] =
{
	0x0180,
	0x0180,
	0x03C0,
	0x03C0,
	0x07E0,
	0x07E0,
	0x0FF0,
	0x0FF0,
	0x1FF8,
	0x1FF8,
	0x3FFC,
	0x3FFC,
	0x7FFE,
	0x7FFE,
	0xFFFF,
	0xFFFF
};

const /*UINT16*/ start_button_bitmap[HEIGHT_32] =	/*bitmap is 32x64 can't use UINT16*/
{
	0xFFFFFFFFFFFFFFFF,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x81CE79CE3D2FBDC1,
	0x8129421021A22121,
	0x81CE718C396239C1,
	0x810A404221222141,
	0x81097B9C3D223D21,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x800F981DF339F001,
	0x8002242044A44001,
	0x8002241847D84001,
	0x8002240444A84001,
	0x8002183844A44001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0x8000000000000001,
	0xFFFFFFFFFFFFFFFF
};

/*The bottom edge of the top portion of the obstacle.*/
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

/*The top edge of the bottom portion of the obstacle.*/
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