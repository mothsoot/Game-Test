#pragma once

#include "main.h"

// POSITIONS & SPEED
//int player_gravity; // 56 subpixels
const float acceleration_speed = 0.046875; // 12 subpixels
const float deceleration_speed = 0.5; // 128 subpixels
const float friction_speed = 0.046875; // 12 subpixels
const float top_speed = 6;

const float gravity_force = 0.21875; // 56 subpixels
const float air_acceleration_speed = 0.09375; // 24 subpixels

const float jump_force = 6.5;
const float jump_release = -4;

const float roll_friction_speed = 0.0234375;
const float roll_deceleration_speed = 0.125;

struct Player {
	int x = 5; // x position
	int y = 5; // y position

	float ySpeed; // vertical velocity
	float xSpeed; // horizontal velocity
	float groundSpeed; // velocity along ground
	float groundAngle;

	int hRadius = 19; // 14 when jump/roll
	int wRadius = 9; // 7 when jump/roll
	int pushRadius = 10;

	int hitbox_y = (hRadius - 3) * 2;
	int hitbox_x = 8 * 2;

	SDL_Rect sprite;
};

// collisions
struct sensor {
    int x;
    int y;
    int distance;
    float tile_angle;
    float tile_id;
};

sensor sensorA(Player player);
sensor sensorB(Player player);
sensor sensorC(Player player);
sensor sensorD(Player player);
sensor sensorE(Player player);
sensor sensorF(Player player);

// speeds
float get_groundSpeed(int input, Player player);
float get_xSpeed(Player player);
float get_ySpeed(Player player);

// misc.
void airAcceleration(int input, Player player);
void gravity(Player player);
void airDrag(Player player);
void airRotation(Player player);