#pragma once
#include <SDL.h>
#include "Game.h"

Game::Game()
{
	snake = new Snake();
	render = new Render();
	
	sizeX = 31;
	sizeY = 23;

	food = { {2, 2}, {255, 0, 0, 255} };
}


Game::~Game()
{
	delete snake;
	delete render;
}

//Game Loop
void Game::loop() {
	SDL_Event e;
	running = true;
	while (running) {
		//Handle keyinput
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				printf("quitting (X)");
				running = false;
			}
			else if (e.type == SDL_KEYDOWN) {
				//Todo: Prevent moving "backwards"
				/*switch (e.key.keysym.sym) {

				case SDLK_LEFT:
					snake->direction = snake->LEFT;
					break;
				case SDLK_RIGHT:
					snake->direction = snake->RIGHT;
					break;
				case SDLK_UP:
					snake->direction = snake->UP;
					break;
				case SDLK_DOWN:
					snake->direction = snake->DOWN;
					break;
				
				case SDLK_r:
					snake->restart();
					break;
				}*/

				 SDL_Keycode k = e.key.keysym.sym;
				 
				 if ((k == SDLK_LEFT || k == SDLK_a) && (snake->direction != snake->RIGHT))
					 snake->direction = snake->LEFT;
				 else if ((k == SDLK_RIGHT || k == SDLK_d) && (snake->direction != snake->LEFT))
					 snake->direction = snake->RIGHT;
				 else if ((k == SDLK_UP || k == SDLK_w) && (snake->direction != snake->DOWN))
					 snake->direction = snake->UP;
				 else if ((k == SDLK_DOWN || k == SDLK_s) && (snake->direction != snake->UP))
					 snake->direction = snake->DOWN;
				 else if (k == SDLK_r)
					 snake->restart();
					

			}
		}
		if (timerFlag) {
			//Ready for a new game tick
			timerFlag = false;
			gameTick();
		}
		//gametick(render, game);
		render->draw(snake, sizeX, sizeY, food);
	}
	
}

Uint32 gameTickCallBack(Uint32 interval, void* th) {
	//timerFlag = true;
	Game* game = (Game*)th;
	game->timerFlag = true;
	return(interval);
}

void Game::gameTick() {
	//printf("tick");
	snake->tick1();
	//Todo: check if snake is still alive
	if (snake->head.point.x >= sizeX || snake->head.point.x < 0 || snake->head.point.y >= sizeY || snake->head.point.y < 0
	|| snake->collideWithSelf()) {
		restart();
		return;
	}
	if (snake->head.point.x == food.point.x && snake->head.point.y == food.point.y) {
		//snake->grow(1);
		snake->growWith(food);
		SDL_SetWindowTitle(render->gWindow, ("Score: " + std::to_string(snake->body.size()) + ", | CPPSnake by Evan Jesty").c_str());
		food = getRandomFood(1000, 0);
	}

	snake->tick2();
}

void Game::start() {
	gameTimerId = SDL_AddTimer(50, gameTickCallBack, this);
	food = getRandomFood(1000, 0);
	SDL_SetWindowTitle(render->gWindow, ("Score: " + std::to_string(snake->body.size()) + ", | CPPSnake by Evan Jesty").c_str());
	loop();
	//Todo: any additonal setup
	render->close();
	render = NULL;
}

void Game::restart() {
	snake->restart();
	food = getRandomFood(1000, 0);
	SDL_SetWindowTitle(render->gWindow, ("Score: " + std::to_string(snake->body.size()) + ", | CPPSnake by Evan Jesty").c_str());
}

Body Game::getRandomFood(int maxIterations, int currentIterations) {
	//if the current iterations is higher than the max, we have failed to find a spot for the food randomly
	if (currentIterations > maxIterations) return { -1, -1 };
	Body body = { {rand() % sizeX, rand() % sizeY}, getRandomColor() };
	bool failed = false;
	if (body.point.x == snake->head.point.x && body.point.y == snake->head.point.y) failed = true;
	//if (body.point.x == sizeX / 2 && body.point.y == sizeY / 2) idk what this check was for (???)
	if (snake->collidesWith(body)) failed = true;

	if (failed) {
		return getRandomFood(maxIterations, currentIterations + 1);
	}

	return body;
}

Color Game::getRandomColor() {
	//Produce vibrant colors, that can't be (white) (in theory)
	int r = (int)(rand() % 3);
	int r1 = (255 - (int)(rand() % 200));
	int r2 = (255 - (int)(rand() % 200));

	if (r == 1) {
		return { r1, r2, 0, 255 };
	}
	else if (r == 2) {
		return { 0, r1, r2, 255 };
	}
	else {
		return {r1, 0, r2, 255};
	}
}
