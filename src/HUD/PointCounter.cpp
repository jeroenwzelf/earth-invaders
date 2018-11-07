#include "PointCounter.h"

void PointCounter::init() {
	x = 0.02; y = 0.07;
	points = 0;
	name = "PointCounter";
}

void PointCounter::draw() {
	draw_text("Score: " + std::to_string(points), x_screen, y_screen);
}

void PointCounter::setPoints(int p) {
	points = p;
}