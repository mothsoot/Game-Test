#include "math.h"

Position& Position::operator+(const Position& p2)
{
	Position p3;
	
	p3.x = x + p2.x;
	p3.y = y + p2.y;

	return p3;
}

Position& Position::operator-(const Position& p2)
{
	Position p3;

	p3.x = x - p2.x;
	p3.y = y - p2.y;

	return p3;
}

Position& Position::operator*(const Position& p2)
{
	Position p3;

	p3.x = x * p2.x;
	p3.y = y * p2.y;

	return p3;
}

Position& Position::operator=(const Position& p)
{
	x = p.x;
	y = p.y;

	return *this;
}

bool Position::operator==(const Position p)
{
	if((p.x == x) && (p.y == y)) {
		return true;
	}
	return false;
}

Position Position::set(int xx, int yy)
{
	x = xx;
	y = yy;

	return *this;
}

Radius Radius::set(int ww, int hh)
{
	w = ww;
	h = hh;

	return *this;
}

Hitbox Hitbox::set(int x, int y, int w, int h)
{
	pos.x = x;
	pos.y = y;

	rad.w = w;
	rad.h = h;

	left = x;
	right = x + (rad.w * 2);
	top = y;
	bottom = y + (rad.h * 2);

	return *this;
}

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
int angle_hex_sin(int hexAngle)
{
	int listIndex = hexAngle % 256;
	return HEX_SINCOSLIST[listIndex];
}

// returns a cosine value from -256 to 255
int angle_hex_cos(int hexAngle)
{
	int listIndex = (hexAngle + 64) % 256;
	return HEX_SINCOSLIST[listIndex];
}

// returns a degree angle converted from a hex angle
int angle_hex_to_degrees(int hexAngle)
{
	return ((256 - hexAngle) / 256) * 360;
}

// returns a hex angle converted from a degree angle
//int angle_degrees_to_hex(float deg_ang)
//{
//	return floor(((360 - deg_ang) / 360) * 256);
//}

int angle_hex_point_direction(int xDist, int yDist)
{
	// default
	if (xDist == 0 && yDist == 0) {
        return 64;
    }

	// force positive
	int xx = absolute(xDist);
	int yy = absolute(yDist);

	int angle = 0;

	// get initial angle
	if (yy >= xx) {
		int compare = (xx * 256) / yy;
		angle = 64 - HEX_ANGLELIST[compare];
	} else {
		int compare = (yy * 256) / xx;
		angle = HEX_ANGLELIST[compare];
	}

	// check angle
	if (xDist <= 0) {
		angle = -angle;
		angle += 128;
	}
		
	if (yDist <= 0) {
		angle = -angle;
		angle += 256;
	}

	return angle;
}