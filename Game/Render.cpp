#include "Render.h"
#include <stdio.h>
#include <iostream>
#include <deque>
#include "Body.h"
Render::Render()
{
	init();
	//SDL_Delay(2000);
}

Render::~Render()
{
	close();
}

bool Render::init() {
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("CPP Snake by Evan Jesty", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);


				return 1;
			}
		}
	}
	return 0;
}

bool Render::close() {
	//Destroy window
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	return 1;
}

bool Render::draw(Snake* snake, int sizeX, int sizeY, Body food) {
	
	//Apply the image
	//SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );
	//Update the surface 

	//Clear screen
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	//Render red filled quad
	//SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };


	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
	SDL_Rect rect = { 0, 0, sizeX * SNAKE_BODY_WIDTH, sizeY * SNAKE_BODY_HEIGHT };
	SDL_RenderDrawRect(gRenderer, &rect);
	for (std::deque<Body>::iterator it = snake->body.begin(); it != snake->body.end(); ++it) {
		rect = { (*it).point.x * SNAKE_BODY_WIDTH, (*it).point.y * SNAKE_BODY_HEIGHT, SNAKE_BODY_WIDTH, SNAKE_BODY_HEIGHT };
		SDL_SetRenderDrawColor(gRenderer, (*it).color.r, (*it).color.g, (*it).color.b, (*it).color.a);
		SDL_RenderFillRect(gRenderer, &rect);
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(gRenderer, &rect);
	}

	SDL_SetRenderDrawColor(gRenderer, food.color.r, food.color.g, food.color.b, food.color.a);
	rect = { food.point.x * SNAKE_BODY_WIDTH, food.point.y * SNAKE_BODY_HEIGHT, SNAKE_BODY_WIDTH, SNAKE_BODY_HEIGHT };
	SDL_RenderFillRect(gRenderer, &rect);
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gRenderer, &rect);

	
	
	//SDL_RenderFillRect(gRenderer, &fillRect);

	//Update screen
	SDL_RenderPresent(gRenderer);

	//SDL_UpdateWindowSurface( gWindow );
	return 1;
}
