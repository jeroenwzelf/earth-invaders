#include "Health.h"

void Health::init() {
	name = "Health";
	x = 0.85f; y = 0.95f;
	heart_size = 80.0f;
	heart_size_half = heart_size / 2;
	space_between = 10.0f;
	health = 3;
}

void Health::draw() {
	for (int i=0; i < health; ++i) {
		float heart_position_x = x_screen + (i * heart_size);
		draw_image(heart_position_x, y_screen, heart_size, heart_size, &animation);
	}
}

void Health::setAnimation(Animation A) {
	animation = A;
}