#pragma once

#include "main.h"
//#include "collision.h"
#include "screen.h"
#include "object.h"

// POSITIONS & SPEED
const float ACCEL_SPEED = 100; // 0.046875; // 12 subpixels
const float DECEL_SPEED = 500; // 0.5; // 128 subpixels
const float FRICTION_SPEED = 100; // 0.046875; // 12 subpixels
const float TOP_SPEED = 500; // 6

const float GRAVITY_FORCE = 0.21875; // 56 subpixels
const float AIR_ACCEL_SPEED = 0.09375; // 24 subpixels

const float JUMP_FORCE = 6.5;
const float JUMP_RELEASE = -4;

const float ROLL_FRICTION_SPEED = 0.0234375;
const float ROLL_DECEL_SPEED = 0.125;

const float SLOPE_FACTOR = 0.125; // 32 subpixels
const float SLOPE_FACTOR_ROLLUP = 0.078125; // 20 subpixels
const float SLOPE_FACTOR_ROLLDOWN = 0.3125; // 80 subpixels

enum COLLISION_MODE {
	FLOOR,
	RWALL,
	CEILING,
	LWALL
};

enum ACTION {
	ACTION_NORMAL,
    ACTION_JUMP,
	ACTION_CROUCH,
    ACTION_ROLL,
    ACTION_SKID,
    ACTION_SPINDASH
};

class Player : public Object {
	public:
		Player(); // : Object();
		~Player();

		void update();
		void move(float time, Player &player);
		// void draw();

		void setxSpeed(SDL_Event e, Player &player);
		void setySpeed(SDL_Event e, Player &player);
		void setFriction(Player &player);
		void setGroundSpeed(SDL_Event e, Player &player); // IMPLEMENT FOR SLOPES

		// COLLISIONS
		int hRadius = 19; // 14 when jump/roll
		int wRadius = 9; // 7 when jump/roll
		int pushRadius = 10;

		// SPRITE
		SDL_Rect sprite = {0, 0, 29, 39};
		SDL_Rect setSprite(int input);
		bool flipSprite;

		float groundSpeed;
        float groundAngle;

		int action;

	private:
        float xSpeed;
        float ySpeed;
};

// air
void airAcceleration(int input, Player player);
void gravity(Player player);
void airDrag(Player player);
void airRotation(Player player);
