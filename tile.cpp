#include "tile.h"

Tile::Tile()
{
    ID = 0;
    type = TILE_NONE;

    sprite.s = {0, 0, 10, 10};
}

void Tile::create(Position p, SDL_Texture* tex)
{
    pos.set(p.x, p.y);

    sprite.s = {0, 0, 10, 10};
    sprite.tex = tex;

    hitbox.set(pos, 10, 10);
}

void Tile::destroy()
{
    SDL_DestroyTexture(sprite.tex);
}

void Tile::draw(Screen screen, Camera cam)
{
    if(checkCollision(hitbox, cam.hitbox)) {
        screen.drawSprite((pos.x - cam.pos.x), (pos.y - cam.pos.y), sprite.s, sprite.tex);
    }
}
