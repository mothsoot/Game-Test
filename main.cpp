#include "main.h"

int main(int argc, char* args[])
{
	// variables
    bool quit = false;
    int x = 5;
    int y = 5;
	
	// initialize SDL
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* image;
	SDL_Texture* texture;
	startUp(window, renderer, image, texture);

	// handle events
	// loop getting player input
	// getting sprite to draw
	// do movement
	// drawing sprite on screen
	while (!quit)
	{
        int input = getInput();
		if(input == QUIT) {
			quit = true;
		}

		SDL_Rect srcrect = spriteDirection(input);
		movement(input, x, y);

		// render sprite at (x, y)
		render(renderer, texture, srcrect, x, y);
		
		// update screen
		SDL_RenderPresent(renderer);
	}

	// shutdown SDL
	shutDown(window, renderer, texture);

	return 0;
}

void startUp(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Surface* &image, SDL_Texture* &texture)
{
	SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Testy Testy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	renderer = SDL_CreateRenderer(window, -1, 0);
        // First  = window drawing in
        // Second = rendering driver (-1 sets to default)
        // Third  = sets SDL_RendererFlags (0 sets to default hardware rendering) 
	image = SDL_LoadBMP("sonic-sprites.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_FreeSurface(image);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set window colour
}

void shutDown(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture)
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	// quit SDL
	SDL_Quit();
}

void render(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect &srcrect, int x, int y)
{
	// destination rectangle
	SDL_Rect dstrect = {x, y, 29, 39}; // x coord, y coord, image width, image height

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, &srcrect, &dstrect);
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

void movement(int input, int &x, int &y)
{
	switch (input) {
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
	}
}

