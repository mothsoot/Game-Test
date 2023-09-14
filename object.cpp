#include "object.h"

void Object::destroy()
{
    SDL_DestroyTexture(sprite.tex);
}

void Object::draw(Screen scr, Camera cam)
{
    if(active) {
        if(checkCol(hitbox, cam.hitbox)) {
            scr.drawFromTop((getxPos() - cam.pos.x), (getyPos() - cam.pos.y), sprite.s, sprite.tex, sprite.flip);
        }
    }
}

bool Object::objectCol(Object* objB)
{
    if(active && objB->active) {
        if(checkCol(hitbox, objB->hitbox)) {
            return true;
        }
    }
    return false;
}
