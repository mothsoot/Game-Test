#pragma once

#include "math.h"
#include "screen.h"
#include "collision.h"

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
        Object() {}
        ~Object() {}

        // void create();
        void destroy();

        virtual void update();
        void draw(Screen scr, SDL_Rect cam);

        int type;

        bool active;

        Position getPos() { return pos; }
        int getxPos() { return pos.x; }
        int getyPos() { return pos.y; }

        Sprite sprite;

        int getwRadius() { return radius.w; }
        int gethRadius() { return radius.h; }
        void setRadius(int h, int w);
        void setRadius(int h, int w, int push);

        int getwHitbox() { return hitbox.w; }
        int gethHitbox() { return hitbox.h; }
        void setHitbox(int h, int w);

    protected:
        Radius radius;
        Radius hitbox;

        Position pos;
        Position setPos(int x, int y);

    private:

};

