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

class Sprite {
    public:
        Sprite(SDL_Texture* t = nullptr): tex(t) {}
        ~Sprite() {}

        SDL_Rect s;
            // x, y, w, h
        SDL_Texture* tex;

        Position offset; // pos offset from centre of sprite

        SDL_RendererFlip flip = SDL_FLIP_NONE;
};

class Object {
    public:
        Object(Position p = {0, 0}, SDL_Texture* t = nullptr): pos(p), sprite(t) {}
        ~Object() {}

        void destroy();
        void draw(Screen scr, Camera cam);

        //virtual void create() {}
        virtual void update() {}
        virtual void animate() {}

        bool active;

        int getType() { return type; }

        //void initCenterPos();
        Position getPos() { return pos; }
        int getxPos() { return pos.x; }
        int getyPos() { return pos.y; }

        Hitbox getHitbox() { return hitbox; }
        Hitbox hitbox;

        virtual bool objectCollision(Object* objB);

        Sprite sprite;

    protected:
        Position centerPos;
        int hRadius, wRadius;

        Position pos;

        int type;

        int animFrame = 0;
        const int animSpeed = 10;

    private:

};