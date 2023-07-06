#pragma once

#include "main.h"
#include "collision.h"
#include "screen.h"
#include "object.h"

// POSITIONS & SPEED
const float ACCEL_SPEED = 5; // 0.046875; // 12 subpixels
const float DECEL_SPEED = 25; // 0.5; // 128 subpixels
const float FRICTION_SPEED = 5; // 0.046875; // 12 subpixels
const float TOP_SPEED = 300; // 6

const float GRAVITY_FORCE = 0.21875; // 56 subpixels
const float AIR_ACCEL_SPEED = 200; // 0.09375; // 24 subpixels

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

struct Collide {
	bool floor;
	bool lWall;
	bool rWall;
	bool ceiling;
};

const int PLAYER_SPRITE_HEIGHT = 39;
const int PLAYER_SPRITE_WIDTH = 29;

class Screen;

class InputHandler {
    public:
        InputHandler() {}
        ~InputHandler() {}

        void keyState(SDL_Event e);
        bool keyDown;
        int key;
};

class Player : public Object {
	public:
		Player(); // : Object() {}
		//~Player() {}

		// void create();
		void update();
		void move(float time);
		void draw(Screen screen);
		// void delete();

		float xSpeed;
        float ySpeed;
		float groundSpeed;

		void getxSpeed();
		void getySpeed();
		void setFriction();
		void getGroundSpeed();

		int mode;
		void setMode();

		// SPRITE
		void setSprite();

        float groundAngle;

		int action;

		bool grounded;

		Collide collide;

		InputHandler input;
    
		// STUFF TO WORK ON LATER
		void jumpVelocity();
		void variableJumpHeight();
		void airAcceleration();
		void gravity();
		void airDrag();
		void airRotation();

	private:
};
