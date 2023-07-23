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

        Position getPos() { return pos; }
        int getxPos() { return pos.x; }
        int getyPos() { return pos.y; }


        int HITBOX_HEIGHT;
        int HITBOX_WIDTH;
        Hitbox getHitbox() { return hitbox; }

        virtual bool objectCollision(Object* objB);

    protected:
        Position pos;
        Hitbox hitbox;

        int type;

        Sprite sprite;
        int animFrame = 0;
        const int animSpeed = 10;

    private:

};