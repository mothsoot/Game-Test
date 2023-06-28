#pragma once

#include "main.h"
//#include "collision.h"

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

		void update();
		void move(float time, Player &player);
		// void draw();

		SDL_Rect animation(int input, Player &player);
		bool flipSprite;

		Position pos;
		void setPos(Position &pos);
		Position getPos() { return pos; }
		
		float groundAngle; // angle on ground

		void setSpeed_TEMP(SDL_Event e, Player &player);

		void setxSpeed(SDL_Event e, Player &player);
		void setFriction(Player &player);
		float getxSpeed() { return xSpeed; }
		void setySpeed(SDL_Event e, Player &player);
		float getySpeed() { return ySpeed; }
		void setGroundSpeed(int input, Player &player); // IMPLEMENT FOR SLOPES
		float getGroundSpeed() { return groundSpeed; }

		int hRadius = 19; // 14 when jump/roll
		int wRadius = 9; // 7 when jump/roll
		int pushRadius = 10;

		void setMode(Player &player);
		int getMode() { return mode; }

		void setAction(Player &player);
		int getAction() { return action; }

		bool airborne = false;
		bool rolling = false;

		void setHitbox(Hitbox &hitbox);
		Hitbox getHitbox() { return hitbox; }

		//Collision collisions;

		SDL_Rect sprite = {0, 0, 29, 39};
		SDL_Rect setSprite(int input);

	private:
		float xSpeed = 0; // horizontal velocity in pixels/frame
		float ySpeed = 0; // vertical velocity
		float groundSpeed; // velocity along ground
		
		int mode;

		int action;

		Hitbox hitbox;
};

// air
void airAcceleration(int input, Player player);
void gravity(Player player);
void airDrag(Player player);
void airRotation(Player player);
