#include "screen.h"

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