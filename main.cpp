#include "main.h"

int main(int argc, char* args[])
{
	// game flags
    bool quit = false;
	bool debug = true;

	// initialize screen
	Screen screen;
	if(!screen.startUp()) {
		cerr << "Failed to initialize! SDL_Error: " << SDL_GetError() << endl;
		return 0;
	}

	// load resources
	SDL_Texture* playerSprite = screen.loadPNG("resources/sonic-sprites.png");
	SDL_Texture* ringSprite = screen.loadPNG("resources/ring-sprites.png");

	// initialize camera
	Camera cam;

	// initialize player
	Player player(200, 200, playerSprite);

	// initialize rings
	Ring* ringList = new (std::nothrow) Ring[MAX_RINGS];
	if(ringList == nullptr) {
		cerr << "Memory allocation failed!\n";
		quit = true;
	} else {
		for (int p = 0; p < MAX_RINGS; p++) {
			ringList[p].setPos(50 + (p * 10), 150);
			ringList[p].sprite.tex = ringSprite;
		}
	}

	// handle events
	while (!quit)
	{
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

		update(&player);
		for (int p = 0; p < MAX_RINGS; p++) {
			update(&ringList[p]);
		}
		cam.update(player.getPos());

		// draw background
		screen.drawBG(cam.c);

		// render sprites
		draw(&player, screen, cam);
		for (int p = 0; p < MAX_RINGS; p++) {
			if(objectCollision(player, ringList[p])) {
				player.rings++;
				ringList[p].active = false;
			} else {
				draw(&ringList[p], screen, cam);
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
	destroy(&player);
	for (int p = 0; p < MAX_RINGS; p++) {
		destroy(&ringList[p]);
	}

	// shutdown SDL
	screen.shutDown();

	return 0;
}

void update(Object* obj)
{
    obj->update();
}

void draw(Object* obj, Screen scr, Camera cam)
{
	obj->draw(scr, cam);
}

void destroy(Object* obj)
{
	obj->destroy();
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

	speed << "X SPD: " << player.xSpeed << "\nY SPD: " << player.ySpeed;
	speed << "\nGround SPD: " << player.groundSpeed;
	scr.loadText(speed.str().c_str());
	scr.drawText(1, 10);

	rings << "Rings: " << player.rings;
	scr.loadText(rings.str().c_str());
	scr.drawText(1, (SCREEN_HEIGHT - 40));

	action << "Action: ";
	switch(player.action) {
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