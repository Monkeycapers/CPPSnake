#include "Snake.h"
#include "Body.h"
#include "Color.h"
#include "Point.h"


Snake::Snake()
{
	restart();
}


Snake::~Snake()
{
}

void Snake::grow(int increment) {

	for (int i = 0; i < increment; i++) {
		body.push_front({ head });
	}

}

void Snake::tick1() {
	if (direction == UP) head.point.y -= 1;
	else if (direction == LEFT) head.point.x -= 1;
	else if (direction == RIGHT) head.point.x += 1;
	else if (direction == DOWN) head.point.y += 1;
}

void Snake::tick2() {
	body.push_back(head);
	body.pop_front();
}

void Snake::restart() {
	body.clear();
	head = { FIRST_POINT, color };
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
