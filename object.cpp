#include "object.h"

void Object::destroy()
{
    SDL_DestroyTexture(sprite.tex);
}

void Object::draw(Screen scr, Camera cam)
{
    if(active) {
        if(checkCollision(hitbox, cam.hitbox)) {
            scr.drawSprite((getxPos() - cam.pos.x), (getyPos() - cam.pos.y), sprite.s, sprite.tex, sprite.flip);
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