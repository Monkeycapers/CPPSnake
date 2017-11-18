#pragma once
#include <stdio.h>
#include <deque>
#include <initializer_list>
#include "Body.h"
#include "Point.h"
#include "Color.h"
#include "Util.h"

class Snake
{
public:

	std::deque <Body> body;

	int direction; /* 0 - Down
					  1 - Up
					  2 - Left
					  3 - Right
				   */
	const int UP = 1, DOWN = 0, LEFT = 2, RIGHT = 3;
	const int FIRST_DIRECTION = 0;

	const Point FIRST_POINT = { 0, -1 }; //Grow to be 0, 0 //Todo: Pls no

	Color color = { 0, 0, 0, 255 }; //Black

	Body head;

	void grow(int increment);

	void growWith(Body with);

	void tick1();
	void tick2();

	void restart();

	bool collideWithSelf();

	bool collidesWith(Body b);

	Snake();
	~Snake();



};

