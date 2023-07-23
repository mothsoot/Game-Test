#include "main.h"

int main(int argc, char* args[])
{
	// game flags
    bool quit = false;
	bool debug = true;
	int scrollOffset = 0;

	// initialize screen
	Screen screen;
	if(!screen.startUp()) {
		cerr << "Failed to initialize! SDL_Error: " << SDL_GetError() << endl;
		return 0;
	}

	// initialize camera
	Camera cam;

	// initialize player
	Player player(startPos, screen.playerTexture);
	player.create();

	// initialize rings
	Ring* ringList = new (nothrow) Ring[MAX_RINGS];
	if(ringList == nullptr) {
		cerr << "Error!! Memory allocation failed!\n";
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

		// scroll background
		--scrollOffset;
		if(scrollOffset < -LEVEL_WIDTH) {
			scrollOffset = 0;
		}

		// DRAW
		screen.drawBG(scrollOffset, 0, cam.c);
		screen.drawBG((scrollOffset + LEVEL_WIDTH), 0, cam.c);

		// render sprites
		player.draw(screen, cam);
		for (int p = 0; p < MAX_RINGS; p++) {
			if(!player.objectCollision(&ringList[p])) {
				ringList[p].draw(screen, cam);
			}
		}

		if(debug) {
			debugText(player, cam, screen);
		}

		// delay for frame rate
		SDL_Delay(16);

		screen.present();
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

	coords.str("");
	speed.str("");
	rings.str("");
	action.str("");
	keyPress.str("");
	collision.str("");

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