#pragma once

//#include "main.h"
#include "collision.h"
#include "input.h"
#include "screen.h"
#include "object.h"
#include "math.h"

// POSITIONS & SPEED
const float ACCEL_SPEED = 0.5; //0.046875; // 12 subpixels
const float DECEL_SPEED = 1; // 128 subpixels
const float FRICTION_SPEED = 0.5; //0.046875; // 12 subpixels
const float TOP_SPEED = 5;

const float GRAVITY_FORCE = 0.2; // 0.21875; // 56 subpixels
const float AIR_ACCEL_SPEED = 0.1; // 0.09375; // 24 subpixels

const float JUMP_FORCE = 6.5;
const float JUMP_RELEASE = -4;

const float ROLL_FRICTION_SPEED = 0.0234375;
const float ROLL_DECEL_SPEED = 0.125;

const float SLOPE_FACTOR = 0.125; // 32 subpixels
const float SLOPE_FACTOR_ROLLUP = 0.078125; // 20 subpixels
const float SLOPE_FACTOR_ROLLDOWN = 0.3125; // 80 subpixels

// PLAYER SPRITE
const int PLAYER_SPRITE_HEIGHT = 39;
const int PLAYER_SPRITE_WIDTH = 29;

class Screen;

enum ACTION {
	ACTION_NORMAL,
	ACTION_JUMP,
	ACTION_CROUCH,
	ACTION_LOOKUP,
	ACTION_SKID,
};

class Player: public Object {
	public:
		Player(int x, int y);
		// ~Player(); // use Object class deconstructor

		// void create();
		void update();
		void move();

		float xSpeed;
		float ySpeed;
		float groundSpeed; // for slopes

		float getSpeed(float speed); // pass either groundSpeed or xSpeed

		void getxSpeed(); // get from groundSpeed
		void getySpeed(); // get from groundSpeed
		float setFriction(float speed);

		int mode;
		void setMode();

		// SPRITE
		void setSprite();

		int action;

		bool grounded;

		InputHandler input;

		// STUFF TO WORK ON/WITH LATER
		Collision collide;

		float groundAngle;

		void jumpVelocity();
		void variableJumpHeight();
		void gravity();
		void airDrag();
		void airRotation();

	private:
};
