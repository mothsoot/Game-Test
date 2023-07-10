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
	stringstream coords;
	stringstream collision;
	stringstream speed;

	action.str("");
	keyPress.str("");
	coords.str("");
	collision.str("");
	speed.str("");

	coords << "X: " << player.pos.x << "\nY: " << player.pos.y;
	screen.loadText(coords.str().c_str());
	screen.drawText(1, 0);

	speed << "X Speed: " << player.xSpeed << "\nY Speed: " << player.ySpeed;
	speed << "\nGround Speed: " << player.groundSpeed;
	screen.loadText(speed.str().c_str());
	screen.drawText(1, 10);

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
	screen.drawText(1, (SCREEN_HEIGHT - 30));

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
	screen.loadText(keyPress.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 20));

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
	screen.loadText(collision.str().c_str());
	screen.drawText(1, (SCREEN_HEIGHT - 10));
}