#pragma once

#include "main.h"
#include "collision.h"
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

enum ACTION {
	ACTION_NORMAL,
    ACTION_JUMP,
	ACTION_CROUCH,
	ACTION_LOOKUP,
    ACTION_ROLL,
    ACTION_SKID,
    ACTION_SPINDASH
};

class Screen;

class Player : public Object {
	public:
		Player(); // : Object() {}
		//~Player() {}

		void create();
		void update(SDL_Event e);
		void move(float time);
		void draw(Screen screen);

		float xSpeed;
        float ySpeed;
		float groundSpeed;

		void setxSpeed(SDL_Event e);
		void setySpeed(SDL_Event e);
		void setFriction();
		void setGroundSpeed(SDL_Event e); // IMPLEMENT FOR SLOPES

		int mode;
		void setMode();

		// SPRITE
		void setSprite(int input);

        float groundAngle;

		int action;

		bool grounded = true;

		bool collide;

		float getxSpeed();
		float getySpeed();


		// STUFF TO WORK ON LATER
		void jumpVelocity();
		void variableJumpHeight(SDL_Event e);
		void airAcceleration(SDL_Event e);
		void gravity();
		void airDrag();
		void airRotation();

	private:
};
