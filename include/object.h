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

struct Sprite {
    SDL_Rect s;
    SDL_Texture* tex;

    bool flip = false;
};

class Object {
    public:
        Object() {}
        ~Object() {}

        void destroy();

        virtual void update();
        void draw(Screen scr, Camera cam);

        int type;

        bool active;

        Position setPos(int x, int y);
        Position getPos() { return pos; }
        int getxPos() { return pos.x; }
        int getyPos() { return pos.y; }

        Sprite sprite;
        int animFrame = 0;

        int getwRadius() { return radius.w; }
        int gethRadius() { return radius.h; }

        Hitbox hitbox;

    protected:
        Position pos;

        Radius radius;
        void setRadius(int h, int w);
        void setRadius(int h, int w, int push);

        void setHitbox();

    private:

};

bool objectCollision(Object objA, Object objB);