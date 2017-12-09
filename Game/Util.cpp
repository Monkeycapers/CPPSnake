#pragma once
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "Color.h"

Color getRandomColor() {
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
		return { r1, 0, r2, 255 };
	}
}
