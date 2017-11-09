//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Render.h"
#include "Game.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool running;

int main(int argc, char* args[])
{
	Game* game = new Game();
	game->start();
	delete game;
	system("pause");
	return 0;
}
