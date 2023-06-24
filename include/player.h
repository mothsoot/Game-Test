#pragma once

#include "main.h"
//#include "collision.h"

// POSITIONS & SPEED
const float ACCEL_SPEED = 500; // 0.046875; // 12 subpixels
const float DECEL_SPEED = 100; // 0.5; // 128 subpixels
const float FRICTION_SPEED = 500; // 0.046875; // 12 subpixels
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

enum MODE {
	FLOOR,
	RIGHT_WALL,
	CEILING,
	LEFT_WALL
};

enum ACTION {
	ACTION_NORMAL,
    ACTION_JUMP,
    ACTION_ROLL,
    ACTION_SKID,
    ACTION_SPINDASH,
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

class Player{
	public:
		Player();
		~Player();

		void update();
		void move(float time, Player &player);

		SDL_Rect animation(int input, Player &player);
		bool flipSprite;

		Position pos;
		void setPos(Position &pos);
		Position getPos();

		float ySpeed; // vertical velocity
		float xSpeed; // horizontal velocity
		float groundSpeed; // velocity along ground
		float groundAngle; // angle on ground
		float get_groundSpeed(int input); // IMPLEMENT FOR SLOPES
		float get_xSpeed(int input);
		float get_ySpeed();
		float get_friction();

		int hRadius = 19; // 14 when jump/roll
		int wRadius = 9; // 7 when jump/roll
		int pushRadius = 10;

		int mode = FLOOR;
		void getMode(Player &player);

		int action;

		bool airborne = false;
		bool rolling = false;

		void setHitbox(Hitbox &hitbox);
		Hitbox getHitbox();

		//Collision collisions;

		SDL_Rect sprite = {0, 0, 29, 39};

	private:
		Hitbox hitbox;
};

// air
void airAcceleration(int input, Player player);
void gravity(Player player);
void airDrag(Player player);
void airRotation(Player player);
