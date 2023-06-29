#pragma once

//#include "main.h"

enum OBJECT_TYPE {
    TYPE_UNKNOWN,
    TYPE_PLAYER,
    TYPE_RING
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

class Object {
    public:
        Object() {}
        ~Object() {}

        //virtual void update();
        // virtual void draw();

        Position pos;
        void setPos(Position &pos);

        // Collision collision;
        int hRadius;
        int wRadius;

        Hitbox hitbox;
        //void setHitbox(Player player, Hitbox &hitbox);

        int type;
        
    private:

};
