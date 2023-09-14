#include "screen.h"

bool openFile()
{
	SDL_RWops* file = SDL_RWFromFile("mapping/ring-mapping.txt", "r");
		// r = for reading
		// w = create empty file for writing
		// a = append to a file
		// r+ = for reading & writing to a file that exists
		// w+ = for reading & writing, overwrites file if one with that name exists
		// a+ = for reading & appending
		// *b = open as a binary file (ex. rb, wb, r+b)
	if(file == nullptr) {
		// cerr << "Error!! Could not open file! SDL_Error: " << SDL_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not open file!\n");
		return false;
	}

	int data[10];

	for (int p = 0; p < 10; p++) {
		SDL_RWread(file, &data[p], sizeof(int), 10);
			// file, objects to write to, size of each object, max objects
	}
	return true;
}

bool Screen::startUp() //SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture* &texture)
{
	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		// cerr << "Could not initialize SDL!! SDL_Error: " << SDL_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL!\n");
		return false;
	}
	
	// initialize SDL_Image for image files
	if(IMG_Init(IMG_INIT_PNG) < 0) {
		// cerr << "Could not initialize SDL_Image!! IMG_Error: " << IMG_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL_Image!\n");
		return false;
	}

	// initialize SDL_TTF for fonts
	if(TTF_Init() < 0) {
		// cerr << "Could not initialize SDL_TTF!! TTF_Error: " << TTF_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not initialize SDL_TTF!\n");
		return false;
	}

	// create window to render in
	window = SDL_CreateWindow("Game moment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if(window == nullptr) {
		// cerr << "Window not created! SDL_Error: " << SDL_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window not created!\n");
		return false;
	}

	// create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		// window drawing in, rendering driver (-1 sets to default), sets SDL_RendererFlags
	if(renderer == nullptr) {
		// cerr << "Renderer not created! SDL_Error: " << SDL_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer not created!\n");
		return false;
	}

	if(!loadResources()) {
		return false;
	}

	// set window colour to white
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	return true;
}

void Screen::shutDown()
{
	// deallocate resources
	if(textTex != nullptr) { SDL_DestroyTexture(textTex); }
	if(bgTex != nullptr) { SDL_DestroyTexture(bgTex); }
	if(tileTex != nullptr) { SDL_DestroyTexture(tileTex); }
	SDL_DestroyTexture(playerTex);
	SDL_DestroyTexture(ringTex);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_CloseFont(font);

	// quit SDL & extensions
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Screen::prep()
{
	SDL_RenderClear(renderer);
}

void Screen::present()
{
	// render screen :)!
	SDL_RenderPresent(renderer);
}

void Screen::drawFromTop(int x, int y, SDL_Rect sprite, SDL_Texture* tex, SDL_RendererFlip flip)
{
	// destination rectangle
	SDL_Rect dstrect = {x, (y + sprite.y), sprite.w, sprite.h}; // x pos, y pos, width, height

	SDL_RenderCopyEx(renderer, tex, &sprite, &dstrect, NULL, NULL, flip);
}

void Screen::drawFromCenter(int x, int y, SDL_Rect sprite, SDL_Texture* tex, SDL_RendererFlip flip)
{
	// destination rectangle
	SDL_Rect dstrect;

	SDL_RenderCopyEx(renderer, tex, &sprite, &dstrect, NULL, NULL, flip);
}

void Screen::drawText(int x, int y)
{
	// get text width & height
	int texW, texH;
	SDL_QueryTexture(textTex, NULL, NULL, &texW, &texH);

	// destination rectangle
	SDL_Rect dstrect = {x, y, texW, texH}; // x coord, y coord, image width, image height

	SDL_RenderCopy(renderer, textTex, NULL, &dstrect);
}

void Screen::drawBG(SDL_Rect cam)
{
	SDL_RenderCopy(renderer, bgTex, &cam, NULL);
}

SDL_Texture* Screen::loadPNG(string file)
{
	SDL_Surface* image = IMG_Load(file.c_str());
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, image);
	if(tex == nullptr) {
		// cerr << "Error!! SDL_Error: " << SDL_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Texture not loaded!\n");
	}

	// delete surface
	SDL_FreeSurface(image);

	return tex;
}

SDL_Texture* Screen::loadText(string text)
{
	// render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColour);
	if(textSurface == nullptr) {
		// cerr << "Error!! SDL_Error: " << SDL_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Text not loaded!\n");
		return nullptr;
	}

	// create texture
	textTex = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_FreeSurface(textSurface);

	return textTex;
}

void Screen::loadBGTex(string file)
{
	bgTex = loadPNG(file);
	if(bgTex == nullptr) {
		// cerr << "Background texture not loaded! IMG_Error: " << IMG_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Background texture not loaded!\n");
	}
}

void Screen::loadTileTex(string file)
{
	tileTex = loadPNG(file);
	if(tileTex == nullptr) {
		// cerr << "Tile texture not loaded! IMG_Error: " << IMG_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Tile texture not loaded!\n");
	}
}

bool Screen::loadResources()
{
	// load font
	font = TTF_OpenFont("resources/NiseSegaSonic.ttf", 10);
	if(font == nullptr) {
		// cerr << "Font not loaded! TTF_Error: " << TTF_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Font not loaded!\n");
		return false;
	}

	// load background
	/*bgTexture = loadPNG("resources/background.png");
	if(bgTexture == nullptr) {
		// cerr << "Background texture not loaded! IMG_Error: " << IMG_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Background texture not loaded!\n");
		return false;
	}
	// load tiles
	tileTexture = loadPNG("resources/tiles.png");
	if(tileTexture == nullptr) {
		// cerr << "Tile texture not loaded! IMG_Error: " << IMG_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Tile texture not loaded!\n");
		return false;
	}*/
	// load player sprites
	playerTex = loadPNG("resources/sonic-sprites-v2.png");
	if(playerTex == nullptr) {
		// cerr << "Player sprites not loaded! IMG_Error: " << IMG_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Player sprites not loaded!\n");
		return false;
	}
	// load ring sprites
	ringTex = loadPNG("resources/ring-sprites.png");
	if(ringTex == nullptr) {
		// cerr << "Ring sprites not loaded! IMG_Error: " << IMG_GetError() << endl;
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Ring sprites not loaded!\n");
		return false;
	}

	return true; // all good!!
}

// CAMERA
Camera::Camera()
{
	pos.set();
	c.x = pos.x;
	c.y = pos.y;
	c.w = SCREEN_WIDTH;
	c.h = SCREEN_HEIGHT;

	hitbox.set(pos, c.w, c.h);
}

void Camera::update(Position playerPos)
{
	pos.set((playerPos.x - SCREEN_WIDTH / 2), (playerPos.y - SCREEN_HEIGHT / 2));

	if(pos.x <= 0) {
		pos.x = 0;
	} else if(pos.x >= LEVEL_WIDTH - c.w) {
		pos.x = LEVEL_WIDTH - c.w;
	}

	if(pos.y <= 0) {
		pos.y = 0;
	} else if(pos.y >= LEVEL_HEIGHT - c.h) {
		pos.y = LEVEL_HEIGHT - c.h;
	}

	c.x = pos.x;
	c.y = pos.y;

	hitbox.update(pos);
}