#include "main.h"

int main(int argc, char* args[])
{
	// game flags
	bool quit = false;
	bool debug = false;

	// initialize screen
	Screen screen;
	if(!screen.startUp()) {
		// cerr << "Failed to initialize screen! SDL_Error: " << SDL_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize screen!\n");
		return 0;
	}

	// initialize camera
	Camera cam;

	Tile* tileList = nullptr;
	if(!createTileList(tileList, screen.tileTexture)) {
		// cerr << "Error!! tileList not created!\n";
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "tileList not created!\n");
		quit = true;
	}

	// initialize player
	Player player(startPos, screen.playerTexture);
	player.create();

	// initialize rings
	Ring* ringList = nullptr;
	if(!createRingList(ringList, ringMappings, screen.ringTexture)) {
		// cerr << "Error!! ringList not created!\n";
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "ringList not created!\n");
		quit = true;
	}

	// handle events
	while (!quit) {
		screen.prep();

		SDL_Event e;

		// PollEvent returns 1 if there is an event in queue
		// returns 0 if none
		// while events in queue
		while (SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			}
			if(e.key.keysym.sym == SDLK_d) {
				debug = true;
			}

			player.input.keyState(e);
		}

		// UPDATE
		player.update(tileList);
		// player.groundCollision(getTile(tileList, player.getPos()));

		for (int p = 0; p < MAX_RINGS; p++) {
			ringList[p].update();
		}
		cam.update(player.getPos());

		// DRAW
		screen.drawBG(cam.c);

		for (int p = 0; p < MAX_TILES; p++) {
			tileList[p].draw(screen, cam);
		}

		// render sprites
		for (int p = 0; p < MAX_RINGS; p++) {
			if(!player.objectCollision(&ringList[p])) {
				ringList[p].draw(screen, cam);
			}
		}
		player.draw(screen, cam);

		if(debug) {
			debugText(player, cam, screen);
		}

		// delay for frame rate
		SDL_Delay(16);

		screen.present();
	}

	// shutdown tiles
	for (int p = 0; p < MAX_TILES; p++) {
		tileList[p].destroy();
	}

	// shutdown objects
	player.destroy();
	for (int p = 0; p < MAX_RINGS; p++) {
		ringList[p].destroy();
	}

	// shutdown SDL
	screen.shutDown();

	return 0;
}

// DEBUG STUFF
void debugText(Player player, Camera cam, Screen scr)
{
	stringstream coords, box, speed, rings, action, keyPress, collision;

	coords << "X: " << player.getxPos() << "\nY: " << player.getyPos();
	coords << "\n\n\nCam X: " << cam.c.x << "\nCam Y: " << cam.c.y;
	scr.loadText(coords.str().c_str());
	scr.drawText(1, 0);

	//box << "\nHitbox X: " << player.hitbox.pos.x << "\nHitbox Y: " << player.hitbox.pos.y;
	box << "Left: " << player.hitbox.left << "\nRight: " << player.hitbox.right;
	box << "\nTop: " << player.hitbox.top << "\nBottom: " << player.hitbox.bottom;
	scr.loadText(box.str().c_str());
	scr.drawText(1, 10);

	speed << "X SPD: " << player.getxSpeed() << "\nY SPD: " << player.getySpeed();
	speed << "\nGround SPD: " << player.getGroundSpeed();
	scr.loadText(speed.str().c_str());
	scr.drawText(1, 20);

	rings << "Rings: " << player.rings;
	scr.loadText(rings.str().c_str());
	scr.drawText(1, (SCREEN_HEIGHT - 40));

	action << "Action: ";
	switch(player.getAction()) {
		case ACTION_NORMAL:
			action << "normal";
			break;
		case ACTION_JUMP:
			action << "jump";
			break;
		case ACTION_CROUCH:
			action << "crouch";
			break;
		case ACTION_LOOKUP:
			action << "look up";
			break;
		case ACTION_SKID:
			action << "skid";
			break;
	}
	scr.loadText(action.str().c_str());
	scr.drawText(1, (SCREEN_HEIGHT - 30));

	keyPress << "Key: ";
	if(player.input.isUp()) {
		keyPress << "UP";
	}
	if(player.input.isDown()) {
		keyPress << "DOWN";
	}
	if(player.input.isLeft()) {
		keyPress << "LEFT";
	}
	if(player.input.isRight()) {
		keyPress << "RIGHT";
	}
	if(player.input.isSpace()) {
		keyPress << "SPACE";
	}
	scr.loadText(keyPress.str().c_str());
	scr.drawText(1, (SCREEN_HEIGHT - 20));

	collision << "Collide? ";
	if(player.collide.isFloor()) {
		collision << "floor";
	}
	if(player.collide.isBottomScr()) {
		collision << "bottom";
	}
	if(player.collide.isLeftScr()) {
		collision << "left";
	}
	if(player.collide.isRightScr()) {
		collision << "right";
	}
	if(player.collide.isTopScr()) {
		collision << "top";
	}
	if(player.collide.isNoScr() && !player.collide.isFloor()) {
		collision << "false";
	}
	collision << "\nGrounded? ";
	if(player.grounded) {
		collision << "true";
	} else {
		collision << "false";
	}
	scr.loadText(collision.str().c_str());
	scr.drawText(1, (SCREEN_HEIGHT - 10));
}