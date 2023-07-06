#pragma once

#include <SDL.h>
//#include "screen.h"

enum OBJECT_TYPE {
    TYPE_UNKNOWN,
    TYPE_PLAYER,
    TYPE_RING,
    TYPE_SPRING
};

struct Position {
	int x;
	int y;
};

struct Radius {
    int h;
    int w;
    int push;
};

struct Hitbox {
	Position pos;

    Radius radius;
};

class Object {
    public:
        Object();
        ~Object() {}

        // virtual void create();
        // virtual void draw();
        // virtual void update();

        int type;

        bool active;

        Position pos;
        Position setPos(int x, int y);

        SDL_Rect sprite;
        bool flipSprite;

        // Collision collision;
        Radius radius;
        Radius setRadius(int h, int w);
        Radius setRadius(int h, int w, int push);

        Hitbox hitbox;
        // void setHitbox();
        
    private:

};

