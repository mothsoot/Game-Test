#include "items.h"

// RINGS
void Ring::create(Position p, SDL_Texture* tex)
{
    type = TYPE_RING;
    active = true;

    pos.set(p.x, p.y);
    hitbox.set(pos, 16, 16);

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

    hitbox.update(pos);
}

void Ring::animate()
{
    sprite.s = RING_SPRITES[animFrame / animSpeed]; // slows to 1/4 speed
    animFrame++;

    if(animFrame / animSpeed > 3) {
        animFrame = 0;
    }
}

Ring* createRingList(Position posMap[], SDL_Texture* tex)
{
    Ring* ringList = new (nothrow) Ring[MAX_RINGS];
    if(ringList == nullptr) {
        // cerr << "Error!! ringList not created!\n";
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "ringList not created!\n");
    }

    for (int p = 0; p < MAX_RINGS; p++) {
        ringList[p].create(posMap[p], tex);
    }

    return ringList;
}

Position* loadRingPosMap(string file)
{
    Position* posMap = new (nothrow) Position[MAX_RINGS];
    ifstream inf;

    inf.open(file);
    if (!inf.is_open()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not open file!\n");
    }

    for (int p = 0; p < MAX_RINGS; p++) {
        int x, y;
        inf >> x;
        inf >> y;

        posMap[p].set(x, y);
    }

    inf.close();

    return posMap;
}