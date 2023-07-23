#include "items.h"

// RINGS
void Ring::create(Position p, SDL_Texture* tex)
{
    type = TYPE_RING;
    active = true;

    pos.set(p.x, p.y);
    HITBOX_WIDTH = 6;
    HITBOX_HEIGHT = 6;

    hitbox.set(pos, HITBOX_WIDTH, HITBOX_HEIGHT);

    sprite.s = RING_SPRITES[0];
    sprite.tex = tex;
}

void Ring::update()
{
    if(!active) {
        // not in play
    } else {
        animate();
    }

    hitbox.set(pos, HITBOX_WIDTH, HITBOX_HEIGHT);
}

void Ring::animate()
{
    sprite.s = RING_SPRITES[animFrame / animSpeed]; // slows to 1/4 speed
    animFrame++;

    if(animFrame / animSpeed > 3) {
        animFrame = 0;
    }
}