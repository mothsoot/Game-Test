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

	// initialize player & load sprites
	Player player(20, (SCREEN_HEIGHT - PLAYER_SPRITE_HEIGHT));
	player.sprite.tex = screen.loadSprites("resources/sonic-sprites.png");

	// initialize ring & load sprites
	Ring ring(40, 40);
	ring.sprite.tex = screen.loadSprites("resources/ring.png");

	// handle events
	// loop getting player input
	// getting sprite to draw
	// do movement
	// drawing sprite on screen
	// update
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

		player.update();

		// move player
		//player.move();

		// render sprites
		player.draw(screen);
		ring.draw(screen);

		if(debug) {
			debugText(player, screen);
		}

		// delay for frame rate
		SDL_Delay(16);

		screen.present();
	}

	// shutdown objects
	player.destroy();
	ring.destroy();

	// shutdown SDL
	screen.shutDown();

	return 0;
}

void debugText(Player player, Screen screen)
{
	stringstream action;
	stringstream keyPress;
	stringstream text1;
	stringstream text2;
	stringstream text3;
	stringstream text4;

	action.str("");
	keyPress.str("");
	text1.str("");
	text2.str("");
	text3.str("");
	text4.str("");

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
	screen.loadText(action.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 40));

	keyPress << "Key: ";
	switch(player.input.key) {
		case UP:
			keyPress << "UP";
			break;
		case DOWN:
			keyPress << "DOWN";
			break;
		case LEFT:
			keyPress << "LEFT";
			break;
		case RIGHT:
			keyPress << "RIGHT";
			break;
		case SPACE:
			keyPress << "SPACE";
			break;
	}
	if(player.input.keyDown) {
		keyPress << " PRESS";
	} else {
		keyPress << " RELEASED";
	}
	screen.loadText(keyPress.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 30));

	text1 << "X: " << player.pos.x << "\nY: " << player.pos.y;
	screen.loadText(text1.str().c_str());
	screen.drawText(1, 0);

	text2 << "Collide? ";
	if(player.collide.floor) {
		text2 << "floor";
	}
	if(player.collide.lWall) {
		text2 << "lWall";
	}
	if(player.collide.rWall) {
		text2 << "rWall";
	}
	if(player.collide.ceiling) {
		text2 << "ceiling";
	}
	if(!player.collide.floor && !player.collide.lWall && !player.collide.rWall && !player.collide.ceiling) {
		text2 << "false";
	}
	text2 << "\nGrounded? ";
	if(player.grounded) {
		text2 << "true";
	} else {
		text2 << "false";
	}
	screen.loadText(text2.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 20));

	text3 << "X Speed: " << player.xSpeed << "\nY Speed: " << player.ySpeed;
	text3 << "\nGround Speed: " << player.groundSpeed;
	screen.loadText(text3.str().c_str());
	screen.drawText(1, 10);

	text4 << "Height Radius: " << player.radius.h << "\nWidth Radius: " << player.radius.w;
	screen.loadText(text4.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 10));
}

InputHandler::InputHandler()
{
	keyDown = false;
	key = NONE;
}

void InputHandler::keyState(SDL_Event e)
{
    switch(e.type) {
		case SDL_KEYDOWN:
			keyDown = true;
			switch(e.key.keysym.sym) {
				case SDLK_UP:
					key = UP;
					break;
				case SDLK_DOWN:
					key = DOWN;
					break;
				case SDLK_LEFT:
					key = LEFT;
					break;
				case SDLK_RIGHT:
					key = RIGHT;
					break;
				case SDLK_SPACE:
					key = SPACE;
					break;
				default:
					key = NONE;
					break;
			}
			break;

		case SDL_KEYUP:
			keyDown = false;
			key = NONE;
			break;
	}
}