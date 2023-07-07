#pragma once

#include "screen.h"

/* OBJECT HEIRARCHY

-OBJECT
    - PLAYER
    - ITEM
        - RING
        - SPRING
    - ENEMY

*/

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

struct Sprite {
    SDL_Rect s;
    SDL_Texture* tex;

    bool flip;
};

class Object {
    public:
        Object();
        ~Object() {}

        // void create();
        void destroy();

        void draw(Screen screen);

        int type;

        bool active;

        Position pos;
        Position setPos(int x, int y);

        Sprite sprite;

        Radius radius;
        Radius setRadius(int h, int w);
        Radius setRadius(int h, int w, int push);

        Hitbox hitbox;
        // void setHitbox();

    private:

};

