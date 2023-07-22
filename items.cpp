#include "items.h"

// RINGS
Ring::Ring(int x, int y)
{
    type = TYPE_RING;
    active = true;

    pos.set(x, y);
    rad.set(6, 6); // 16, 16 sprite
    hitbox.set(pos.x, pos.y, rad.w, rad.h);

    sprite.s = ringSprites[0];
}

void Ring::update()
{
    if(!active) {
        // not in play
    } else {
        animate();
    }

    hitbox.set(pos.x, pos.y, rad.w, rad.h);
}

void Ring::animate()
{
    sprite.s = ringSprites[animFrame / 4]; // slows to 1/4 speed
    animFrame++;

    if(animFrame / 4 > 3) {
        animFrame = 0;
    }
}