#pragma once
#include "Render.h"
#include "Snake.h"
#include <string>
class Game
{
public:

	int sizeX;
	int sizeY;

	int speed;

	Body food;

	Snake* snake;
	Render* render;
	void loop();
	bool running;
	bool timerFlag;
	void start();
	void gameTick();
	void restart();
	Color getRandomColor();

	SDL_TimerID gameTimerId;

	//Uint32 gameTickCallBack(Uint32 interval, void *param);

	Game();
	~Game();

private:
	Body getRandomFood(int maxIterations, int currentIterations);
};

