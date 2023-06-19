#include "main.h"

int main(int argc, char* args[])
{
	// variables
    bool quit = false;
	
	// initialize SDL
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* sprite;
	SDL_Texture* texture;
	startUp(window, renderer, sprite, texture);

	// initialize player
	Player player;

	// handle events
	// loop getting player input
	// getting sprite to draw
	// do movement
	// drawing sprite on screen
	// update
	while (!quit)
	{
        int input = getInput();
		if(input == QUIT) {
			quit = true;
		}

		player.sprite = spriteDirection(input);
		movement(input, player);

		// render sprite at (x, y)
		render(renderer, texture, player);
		
		// update screen
		SDL_RenderPresent(renderer);
	}

	// shutdown SDL
	shutDown(window, renderer, texture);

	return 0;
}

void startUp(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &sprite, SDL_Texture* &texture)
{
	SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Testy Testy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
        // First  = window drawing in
        // Second = rendering driver (-1 sets to default)
        // Third  = sets SDL_RendererFlags (0 sets to default hardware rendering) 
	sprite = SDL_LoadBMP("sonic-sprites.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, sprite);

	SDL_FreeSurface(sprite);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set window colour to white
}

void shutDown(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture)
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// quit SDL
	SDL_Quit();
}

void render(SDL_Renderer* renderer, SDL_Texture* texture, Player player)
{
	// destination rectangle
	SDL_Rect dstrect = {player.x, player.y, 29, 39}; // x coord, y coord, image width, image height

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, &player.sprite, &dstrect);
}

int getInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	int input;

	switch (event.type)
	{
		case SDL_QUIT:
			input = QUIT;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_LEFT:
					input = LEFT;
					break;
				case SDLK_RIGHT:
					input = RIGHT;
					break;
				case SDLK_UP:
					input = UP;
					break;
				case SDLK_DOWN:
					input = DOWN;
					break;
			}
			break;
	}
	
	return input;
}

SDL_Rect spriteDirection(int input)
{
	SDL_Rect player;
	static int direction;

	switch (input) {
		case LEFT:
			player = SPRITE_LEFT;
			direction = -1;
			break;
		case RIGHT:
			player = SPRITE_RIGHT;
			direction = 1;
			break;
		case UP:
			if(direction < 0) {
				player = SPRITE_UP_LEFT;
			} else {
				player = SPRITE_UP_RIGHT;
			}
			break;
		case DOWN:
			if(direction < 0) {
				player = SPRITE_DOWN_LEFT;
			} else {
				player = SPRITE_DOWN_RIGHT;
			}
			break;
	}

	return player;
}

void movement(int input, Player &player)
{
	switch (input) {
		case LEFT:
			player.x--;
			break;
		case RIGHT:
			player.x++;
			break;
		case UP:
			player.y--;
			break;
		case DOWN:
			player.y++;
			break;
	}
}

