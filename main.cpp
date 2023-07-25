#include "main.h"

int main(int argc, char* args[])
{
	// game flags
	bool quit = false;
	bool debug = true;

	// initialize screen
	Screen screen;
	if(!screen.startUp()) {
		// cerr << "Failed to initialize screen! SDL_Error: " << SDL_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize screen!\n");
		return 0;
	}

	Position tileMappings[MAX_TILES];
	for (int p = 0; p < MAX_TILES; p++) {
		tileMappings[p].x = 10 * p;
		tileMappings[p].y = 235;
	}

	Tile* tileList = new (nothrow) Tile[MAX_TILES];
	if(tileList == nullptr) {
		// cerr << "Error!! tileList not created!\n";
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "tileList not created!\n");
		quit = true;
	} else {
		for (int p = 0; p < MAX_TILES; p++) {
			tileList[p].create(tileMappings[p], screen.tileTexture);
		}
	}

	// initialize camera
	Camera cam;

	// initialize player
	Player player(startPos, screen.playerTexture);
	player.create();

	// initialize rings
	Ring* ringList = new (nothrow) Ring[MAX_RINGS];
	if(ringList == nullptr) {
		// cerr << "Error!! ringList not created!\n";
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "ringList not created!\n");
		quit = true;
	} else {
		for (int p = 0; p < MAX_RINGS; p++) {
			ringList[p].create(ringsMapping[p], screen.ringTexture);
		}
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

			player.input.keyState(e);
		}

		// UPDATE
		player.update();
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
	stringstream coords, speed, rings, action, keyPress, collision;

	coords << "X: " << player.getxPos() << "\nY: " << player.getyPos();
	coords << "\n\n\nCam X: " << cam.c.x << "\nCam Y: " << cam.c.y;
	scr.loadText(coords.str().c_str());
	scr.drawText(1, 0);

	speed << "X SPD: " << player.getxSpeed() << "\nY SPD: " << player.getySpeed();
	speed << "\nGround SPD: " << player.getGroundSpeed();
	scr.loadText(speed.str().c_str());
	scr.drawText(1, 10);

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
	if(player.collide.islWall()) {
		collision << "lWall";
	}
	if(player.collide.isrWall()) {
		collision << "rWall";
	}
	if(player.collide.isCeiling()) {
		collision << "ceiling";
	}
	if(player.collide.isNone()) {
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