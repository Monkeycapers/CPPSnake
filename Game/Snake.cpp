#include "Snake.h"
#include "Body.h"
#include "Color.h"
#include "Point.h"
#include <iostream>

Snake::Snake()
{
	restart();
}


Snake::~Snake()
{
}

void Snake::grow(int increment) {

	for (int i = 0; i < increment; i++) {
		body.push_front({head});
	}

}

void Snake::growWith(Body with) {
	body.push_front({ with });
	head = with;
	//std::cout << "\n" << with.point.x << " " << with.point.y << ", " << with.color.r << " " << with.color.g << " " << with.color.b << std::endl;
	//std::cout << "\n" << head.point.x << " " << head.point.y << ", " << head.color.r << " " << head.color.g << " " << head.color.b << std::endl;
}

void Snake::tick1() {
	if (direction == UP) head.point.y -= 1;
	else if (direction == LEFT) head.point.x -= 1;
	else if (direction == RIGHT) head.point.x += 1;
	else if (direction == DOWN) head.point.y += 1;
}

void Snake::tick2() {
	Body b = body.front();
	body.pop_front();
	body.push_back({ {head.point.x, head.point.y}, {b.color.r, b.color.g, b.color.b, b.color.a} });
	
}

void Snake::restart() {
	body.clear();
	head = { FIRST_POINT, getRandomColor() };
	grow(1);
	direction = FIRST_DIRECTION;
	
}

bool Snake::collideWithSelf() {
	return collidesWith(head);
}

bool Snake::collidesWith(Body b) {
	for (std::deque<Body>::iterator it = body.begin(); it != body.end(); ++it) {
		if ((*it).point.x == b.point.x && (*it).point.y == b.point.y) return true;
	}
	return false;
}
