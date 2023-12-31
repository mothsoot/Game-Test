#pragma once

#include <cmath>

class Position {
    public:
        Position(int xx = 0, int yy = 0): x(xx), y(yy) {}

        int x, y;

        Position set(int xx = 0, int yy = 0);

        Position& operator+(const Position& p2);
        Position& operator-(const Position& p2);
        Position& operator*(const Position& p2);
        Position& operator=(const Position& p);
        bool operator==(const Position p);
};

class Hitbox {
    public:
        Hitbox(Position p = {0, 0}, int w = 0, int h = 0): pos(p), width(w), height(h) {}

        Position pos;
        int height, width;
        int left, right, top, bottom;

        Hitbox set(Position p, int w, int h, int offset = 0);
        void update(Position p);
};

int sign(float x); // get sign of x
int absolute(int x); // get positive version of x

// SUBPIXELS

// uses subpixels instead of decimal values
// 1-256

int subpixel_to_decimal(int pixel, int subpixel);

// HEX ANGLES

// uses hex values instead of degrees for angles
// 0-255, 256 = 0
// hex angles go clockwise, degrees go counterclockwise

const int HEX_SINCOSLIST[] = {0,6,12,18,25,31,37,43,49,56,62,68,74,80,86,92,97,103,109,115,120,126,131,136,142,147,152,157,162,167,171,176,181,185,189,193,197,201,205,209,212,216,219,222,225,228,231,234,236,238,241,243,244,246,248,249,251,252,253,254,254,255,255,255,
256,255,255,255,254,254,253,252,251,249,248,246,244,243,241,238,236,234,231,228,225,222,219,216,212,209,205,201,197,193,189,185,181,176,171,167,162,157,152,147,142,136,131,126,120,115,109,103,97,92,86,80,74,68,62,56,49,43,37,31,25,18,12,6,
0,-6,-12,-18,-25,-31,-37,-43,-49,-56,-62,-68,-74,-80,-86,-92,-97,-103,-109,-115,-120,-126,-131,-136,-142,-147,-152,-157,-162,-167,-171,-176,-181,-185,-189,-193,-197,-201,-205,-209,-212,-216,-219,-222,-225,-228,-231,-234,-236,-238,-241,-243,-244,-246,-248,-249,-251,-252,-253,-254,-254,-255,-255,-255,
-256,-255,-255,-255,-254,-254,-253,-252,-251,-249,-248,-246,-244,-243,-241,-238,-236,-234,-231,-228,-225,-222,-219,-216,-212,-209,-205,-201,-197,-193,-189,-185,-181,-176,-171,-167,-162,-157,-152,-147,-142,-136,-131,-126,-120,-115,-109,-103,-97,-92,-86,-80,-74,-68,-62,-56,-49,-43,-37,-31,-25,-18,-12,-6};

const int HEX_ANGLELIST[] = {0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,6,6,6,7,7,7,7,7,7,8,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,10,11,11,11,11,11,11,11,12,12,12,12,12,12,12,13,13,13,13,13,13,13,14,14,14,14,14,14,14,15,15,15,15,15,15,15,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,18,18,18,18,18,18,18,19,19,19,19,19,19,19,19,20,20,20,20,20,20,20,20,21,21,21,21,21,21,21,21,21,22,22,22,22,22,22,22,22,23,23,23,23,23,23,23,23,23,24,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,30,30,30,30,30,30,30,30,30,30,30,31,31,31,31,31,31,31,31,31,31,31,31,32,32,32,32,32,32,32,0};

// returns a sine value from -256 to 255
int angle_hex_sin(int hexAngle);

// returns a cosine value from -256 to 255
int angle_hex_cos(int hexAngle);

// returns a degree angle converted from a hex angle
int angle_hex_to_degrees(int hexAngle);

// returns a hex angle converted from a degree angle
int angle_degrees_to_hex(float degreeAngle);

// returns a hex angle representing a direction from one point to another 
// effectively these points are represented by [0, 0] and [xdist, ydist]
int angle_hex_point_direction(int xDist, int yDist);