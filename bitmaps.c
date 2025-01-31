#define HEIGHT_32 32
#define S_BIRD_HEIGHT 16

typedef unsigned long UINT32
typedef unsigned int UINT16

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
	0xC3CC0C03,
	0xC3CC0C03,
	0xC033303C,
	0xC033303C,
	0x0C33330C,
	0x0C33330C,
	0x030CF30F,
	0x030CF30F,
	0x00CC0003,
	0x00CC0003,
	0x003000FF,
	0x003000FF,
	0x00000F00,
	0x00000F00,
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
	0x00000F00,
	0x00000F00,
	0x003000FF,
	0x003000FF,
	0x00CC0003,
	0x00CC0003,
	0x030CF3CF,
	0x0C33330C,
	0x0C33330C,
	0xC033303C,
	0xC033303C,
	0xC3CC0C03,
	0xC3CC0C03,
	0xC0303FC3,
	0xC0303FC3,
	0xC3C00033,
	0xC3C00033,
	0xFC00000F,
	0xFC00000F
};

const UINT32 zero_bitmap[HEIGHT_32] =
{
	0xFF0011FF,
	0xFF0011FF,
	0xFF0011FF,
	0xFF0011FF,
	0xFF0011FF,
	0xFF0011FF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0x88FFEEFF,
	0xFF0011FF,
	0xFF0011FF,
	0xFF0011FF,
	0xFF0011FF,
	0xFF0011FF,
	0xFF0011FF
};

const UINT32 one_bitmap[HEIGHT_32] =
{
	0x
}

const UINT32 two_bitmap[HEIGHT_32] =
{
	0x
}

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
}

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
}

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
}

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
}

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
}

const UINT32 eight_bitmap[HEIGHT_32] =
{
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC0FFF30F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
	0xC000000F,
}

const UINT32 nine_bitmap[HEIGHT_32] =
{
	0x
}