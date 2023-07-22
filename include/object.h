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

struct Sprite {
    SDL_Rect s;
    SDL_Texture* tex;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
};

class Object {
    public:
        Object() {}
        ~Object() {}

        void create(int x, int y, SDL_Texture* spriteTex);
        void destroy();
        void draw(Screen scr, Camera cam);

        virtual void update() {}
        virtual void animate() {}

        int type;
        bool active;


        Position getPos() { return pos; }
        int getxPos() { return pos.x; }
        int getyPos() { return pos.y; }

        Sprite sprite;
        int animFrame = 0;

        int getwRad() { return rad.w; }
        int gethRad() { return rad.h; }

        Hitbox hitbox;

        virtual bool objectCollision(Object* objB);

    protected:
        Position pos;
        Radius rad;

        void setHitbox();

    private:

};