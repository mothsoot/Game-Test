#include "screen.h"

bool Screen::startUp() //SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture)
{
	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "Could not initialize SDL!! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}
	
	// initialize SDL_Image for image files
	if(IMG_Init(IMG_INIT_PNG) < 0) {
		cerr << "Could not initialize SDL_Image!! IMG_Error: " << IMG_GetError() << endl;
		return false;
	}

	// initialize SDL_TTF for fonts
	if(TTF_Init() < 0) {
		cerr << "Could not initialize SDL_TTF!! TTF_Error: " << TTF_GetError() << endl;
		return false;
	}

	// create window to render in
	window = SDL_CreateWindow("Game moment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if(window == NULL) {
		cerr << "Window not created! SDL_Error: " << SDL_GetError() << endl;
		return false;
	}

	// create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		// window drawing in, rendering driver (-1 sets to default), sets SDL_RendererFlags
	if(renderer == nullptr) {
		cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
		return false;
	}

	// load font
	font = TTF_OpenFont("resources/NiseSegaSonic.ttf", 10);
	// load background
	bgTexture = loadPNG("resources/bg.png");

	// set window colour to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	return true;
}

void Screen::shutDown()
{
	// deallocate resources
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = nullptr;

	TTF_CloseFont(font);

	// quit SDL & extensions
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Screen::prep()
{
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // set window colour to white
}

void Screen::present()
{
	// render screen :)!
	SDL_RenderPresent(renderer);
}

void Screen::drawSprite(int x, int y, SDL_Rect sprite, SDL_Texture* tex, SDL_RendererFlip flip)
{
	// destination rectangle
	SDL_Rect dstrect = {x, (y + sprite.y), sprite.w, sprite.h}; // x coord, y coord, image width, image height

	SDL_RenderCopyEx(renderer, tex, &sprite, &dstrect, NULL, NULL, flip);
}

void Screen::drawText(int x, int y)
{
	// get text width & height
	int texW, texH;
	SDL_QueryTexture(textTexture, NULL, NULL, &texW, &texH);

	// destination rectangle
	SDL_Rect dstrect = {x, y, texW, texH}; // x coord, y coord, image width, image height

	SDL_RenderCopy(renderer, textTexture, NULL, &dstrect);
}

void Screen::drawBG(SDL_Rect cam)
{
	SDL_RenderCopy(renderer, bgTexture, &cam, NULL);
}

SDL_Texture* Screen::loadPNG(string file)
{
	SDL_Surface* image = nullptr;

	image = IMG_Load(file.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

	// delete image
	SDL_FreeSurface(image);

	return texture;
}

SDL_Texture* Screen::loadText(string text)
{
	// render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);

	// create texture
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_FreeSurface(textSurface);

	return textTexture;
}

// CAMERA
Camera::Camera()
{
	c.x = 0;
	c.y = 0;
	c.w = SCREEN_WIDTH;
	c.h = SCREEN_HEIGHT;
}

void Camera::update(Position playerPos)
{
	c.x = playerPos.x - SCREEN_WIDTH / 2; //  + sprite.w / 2
	c.y = playerPos.y - SCREEN_HEIGHT / 2; // + sprite.h / 2

	if(c.x <= 0) {
		c.x = 0;
	} else if(c.x >= LEVEL_WIDTH - c.w) {
		c.x = LEVEL_WIDTH - c.w;
	}

	if(c.y <= 0) {
		c.y = 0;
	} else if(c.y >= LEVEL_HEIGHT - c.h) {
		c.y = LEVEL_HEIGHT - c.h;
	}

	hitbox.set(c.x, c.y, c.w, c.h);
}