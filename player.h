#pragma once

#include "main.h"

// POSITIONS & SPEED
//int player_gravity; // 56 subpixels
const float acceleration_speed = 0.046875; // 12 subpixels
const float deceleration_speed = 0.5; // 128 subpixels
const float friction_speed = 0.046875; // 12 subpixels
const float top_speed = 6;

struct Player {
	int x = 5;
	int y = 5;

	float ySpeed;
	float xSpeed;
	float ground_speed;
	float ground_angle;

	int hRadius = 19; // 14 when jump/roll
	int wRadius = 9; // 7 when jump/roll
	int pushRadius = 10;

	float jump_force = 6.5; // 6 pixels & 128 subpixels

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