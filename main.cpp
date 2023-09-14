#include "main.h"

int main(int argc, char* args[])
{
	// game flags
	bool quit = false;

	// initialize screen
	Screen screen;
	if(!screen.startUp()) {
		// cerr << "Failed to initialize screen! SDL_Error: " << SDL_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize screen!\n");
		return 0;
	}

	// initialize camera
	Camera cam;

	menu(screen, cam, quit);
	game(screen, cam, quit);

	// shutdown tiles
	/*for (int p = 0; p < MAX_TILES; p++) {
		tileList[p].destroy();
	}

	// shutdown objects
	player.destroy();
	for (int p = 0; p < MAX_RINGS; p++) {
		ringList[p].destroy();
	}*/

	// shutdown SDL
	screen.shutDown();

	return 0;
}

void menu(Screen &screen, Camera cam, bool &quit)
{
	InputHandler input;
	bool menu = true;

	screen.loadBGTex("resources/bg-menu.png");

	stringstream text;
	text << "Game time!! Click anywhere to begin.";
	screen.loadText(text.str().c_str());

	while (menu) {
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
				menu = false;
			}
			input.mouseState(e);
		}
		if(input.isMouseLeft()) { //&& (input.getMousePos() == button.pos)) {
			menu = false;
			level = 1;
		}
		if(input.isMouseRight()) {
			menu = false;
			level = 2;
		}

		// draw
		screen.prep();

		screen.drawBG(cam.c);
		screen.drawText(40, 50);

		screen.present();
	}
}

void game(Screen &screen, Camera cam, bool &quit)
{
	bool debug = false;

	Tile* tileList = nullptr;
	Ring* ringList = nullptr;

	switch (level) {
		case 1:
			// load background for level
			screen.loadBGTex("resources/bg-01.png");
			// load tile sprites for level
			screen.loadTileTex("resources/tiles-01.png");

			// load tile maps
			tileList = createTileList(loadPosMap("layouts/tiles-pos-01.txt"), 
				loadTypeMap("layouts/tiles-id-01.txt"), loadColMap("layouts/tiles-col-01.txt"));

			// load ring map & create list
			ringList = createRingList(loadRingPosMap("layouts/rings-pos-01.txt"), screen.getRingTex());
			break;

		case 2:
			screen.loadBGTex("resources/bg-01.png");
			screen.loadTileTex("resources/tiles-02.png");

			tileList = createTileList(loadPosMap("layouts/tiles-pos-02.txt"), 
				loadTypeMap("layouts/tiles-id-02.txt"), loadColMap("layouts/tiles-col-02.txt"));

			ringList = createRingList(loadRingPosMap("layouts/rings-pos-02.txt"), screen.getRingTex());

			break;
	}

	// initialize player
	Player player(startPos, screen.getPlayerTex());
	player.create();

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
			if(e.key.keysym.sym == SDLK_q) {
				debug = true;
			}

			player.input.keyState(e);
		}

		// UPDATE
		player.update(tileList, quit);
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
			if(!player.objectCol(&ringList[p])) {
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
	if(player.col.isFloor()) {
		collision << "floor";
	}
	if(player.col.isBottomScr()) {
		collision << "bottom";
	}
	if(player.col.isLeftScr()) {
		collision << "left";
	}
	if(player.col.isRightScr()) {
		collision << "right";
	}
	if(player.col.isTopScr()) {
		collision << "top";
	}
	if(player.col.isNoneScr() && !player.col.isFloor()) {
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