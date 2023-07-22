#include "object.h"

void Object::create(int x, int y, SDL_Texture* spriteTex)
{
    pos.set(x, y);
    sprite.tex = spriteTex;
}

void Object::destroy()
{
    SDL_DestroyTexture(sprite.tex);
}

void Object::draw(Screen scr, Camera cam)
{
    if(active) {
        if(checkCollision(hitbox, cam.hitbox)) {
            scr.drawSprite((pos.x - cam.c.x), (pos.y - cam.c.y), sprite.s, sprite.tex, sprite.flip);
        }
    }
}

bool Object::objectCollision(Object* objB)
{
    if(active && objB->active) {
        if(checkCollision(hitbox, objB->hitbox)) {
                return true;
        }
    }
    return false;
}