#include "math.h"

int sign(float x)
{
	if(x < 0) {
		return -1;
	} else if(x > 0) {
		return 1;
	} else {
		return 0;
	}
}

int absolute(int x)
{
	if(x < 0) {
		x = x * -1;
	}

	return x;
}

// SUBPIXELS

int subpixel_to_decimal(int pixel, int subpixel)
{
	return pixel + (subpixel / 256);
}

// HEX ANGLES

// returns a sine value from -256 to 255
int angle_hex_sin(int hex_ang)
{
	int list_index = hex_ang % 256;
	return HEX_SINCOSLIST[list_index];
}

// returns a cosine value from -256 to 255
int angle_hex_cos(int hex_ang)
{
	int list_index = (hex_ang + 64) % 256;
	return HEX_SINCOSLIST[list_index];
}

// returns a degree angle converted from a hex angle
int angle_hex_to_degrees(int hex_ang)
{
	return ((256 - hex_ang) / 256) * 360;
}

// returns a hex angle converted from a degree angle
//int angle_degrees_to_hex(float deg_ang)
//{
//	return floor(((360 - deg_ang) / 360) * 256);
//}

int angle_hex_point_direction(int xdist, int ydist)
{
	// default
	if (xdist == 0 && ydist == 0) {
        return 64;
    }

	// force positive
	int xx = absolute(xdist);
	int yy = absolute(ydist);
		
	int angle = 0;
		
	// Get initial angle
	if (yy >= xx) {
		int compare = (xx * 256) / yy;
		angle = 64 - HEX_ANGLELIST[compare];
	} else {
		int compare = (yy * 256) / xx;
		angle = HEX_ANGLELIST[compare];
	}
		
	// Check angle
	if (xdist <= 0) {
		angle = -angle;
		angle += 128;
	}
		
	if (ydist <= 0) {
		angle = -angle;
		angle += 256;
	}

	return angle;
}