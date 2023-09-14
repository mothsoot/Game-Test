#pragma once

#include "collision.h"
#include "input.h"
#include "screen.h"
#include "tile.h"
#include "object.h"
#include "math.h"

// POSITIONS & SPEED
const float ACCEL_SPEED = 0.5; //0.046875; // 12 subpixels
const float DECEL_SPEED = 1; // 128 subpixels
const float FRICTION_SPEED = 0.5; //0.046875; // 12 subpixels
const float TOP_SPEED = 6;

const float GRAVITY_FORCE = 0.2; // 0.21875; // 56 subpixels
const float AIR_ACCEL_SPEED = 0.1; // 0.09375; // 24 subpixels

const float JUMP_FORCE = 6.5;
const float JUMP_RELEASE = -4;

const float SLOPE_FACTOR = 0.125; // 32 subpixels

enum ACTION {
	ACTION_NORMAL,
	ACTION_JUMP,
	ACTION_CROUCH,
	ACTION_LOOKUP,
	ACTION_SKID,
};

class Player: public Object {
	public:
		Player(Position pos = {0, 0}, SDL_Texture* tex = nullptr): Object(pos, tex) { }

		virtual void create();
		virtual void update(Tile* tileList, bool &quit);
		virtual void animate();

		bool grounded;
		float groundAngle;

		int getAction() { return action; }
		int rings;

		float getxSpeed() { return xSpeed; }
		float getySpeed() { return ySpeed; }
		float getGroundSpeed() { return groundSpeed; }

		InputHandler input;

		Collision col;
		void groundCol(Tile* tile);
		virtual bool objectCol(Object* objB);

	private:
		void move();

		int action;

		float xSpeed;
		float ySpeed;
		float groundSpeed; // for slopes

		float setSpeed(float speed); // pass either groundSpeed or xSpeed
		void setxSpeed(); // get from groundSpeed
		void setySpeed(); // get from groundSpeed
		float setFriction(float speed);

		void jump();
		void airRotation();
};
