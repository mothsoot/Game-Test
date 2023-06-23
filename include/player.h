#pragma once

#include "main.h"
//#include "collision.h"

// POSITIONS & SPEED
const float acceleration_speed = 500; // 0.046875; // 12 subpixels
const float deceleration_speed = 100; // 0.5; // 128 subpixels
const float friction_speed = 500; // 0.046875; // 12 subpixels
const float top_speed = 500; // 6

const float gravity_force = 0.21875; // 56 subpixels
const float air_acceleration_speed = 0.09375; // 24 subpixels

const float jump_force = 6.5;
const float jump_release = -4;

const float roll_friction_speed = 0.0234375;
const float roll_deceleration_speed = 0.125;

const float slope_factor = 0.125; // 32 subpixels
const float slope_factor_rollup = 0.078125; // 20 subpixels
const float slope_factor_rolldown = 0.3125; // 80 subpixels

enum MODE {FLOOR, RIGHT_WALL, CEILING, LEFT_WALL};

struct Position {
	int x;
	int y;
};

struct Hitbox {
	Position pos;

	int hRadius;
	int wRadius;
};

class Player {
	public:
		Player();
		~Player();

		Position pos;
		float x; // x position
		float y; // y position

		float ySpeed; // vertical velocity
		float xSpeed; // horizontal velocity
		float groundSpeed; // velocity along ground
		float groundAngle; // angle on ground

		int hRadius = 19; // 14 when jump/roll
		int wRadius = 9; // 7 when jump/roll
		int pushRadius = 10;

		Hitbox hitbox;
		void setHitbox(Hitbox &hitbox);
		Hitbox getHitbox();

		//Collision collisions;

		int mode;

		SDL_Rect sprite = {0, 0, 29, 39};

		float get_groundSpeed(int input); // IMPLEMENT FOR SLOPES
		float get_xSpeed(int input);
		float get_ySpeed();
		float get_friction();

		void setPos(Position &pos);
		Position getPos();

	private:
};

// air
void airAcceleration(int input, Player player);
void gravity(Player player);
void airDrag(Player player);
void airRotation(Player player);
