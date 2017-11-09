#pragma once
#include <SDL.h>
#include "Snake.h"
#include "Point.h"
class Render
{
public:

	//Screen dimension constants
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	const int SNAKE_BODY_HEIGHT = 20;
	const int SNAKE_BODY_WIDTH = 20;

	//The window we'll be rendering to 
	SDL_Window* gWindow = NULL;
	//The surface contained by the window 
	SDL_Surface* gScreenSurface = NULL;
	//The renderer
	SDL_Renderer* gRenderer = NULL;

	//The image we will load and show on the screen
	//SDL_Surface* gHelloWorld = NULL;

	Render();
	~Render();

	bool init();
	bool close();
	bool draw(Snake* snake, int sizeX, int sizeY, Body food);
};

