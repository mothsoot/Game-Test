#include "ring.h"

void Ring::create()
{
    type = TYPE_RING;

    setPos(50, 50);
    setRadius(8, 8);

    sprite = SPRITE_RING;
}

void Ring::draw(Screen screen)
{
    screen.drawSprite(pos.x, pos.y, sprite);
}